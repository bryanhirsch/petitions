<?php
/**
 * @file
 * Page callbacks and related functions for petitions_stats_users module.
 */

/**
 * Page callback for Users Statistics.
 *
 * Generates an array of user statistics for a given date.
 * Searches through all relevant JSON files to build a nested
 * array of user statistics, sorted by date and hour.
 *
 * @param string $date
 *   A date matching the format yyyy-mm-dd.
 *   This is used to select the appropriate data directory.
 */
function petitions_stats_users_page($date = NULL) {
  $output = '';

  // Set default date params.
  $format = 'Y-m-d';
  if (!$date) {
    $date = date($format);
  }

  // Build date selector form.
  $date_form = drupal_render(drupal_get_form('petitions_stats_users_date_form', $date, $format));
  $output .= $date_form;

  $base_dir = variable_get('petitions_stats_users_data_dir', 'petitions_stats_users_data');
  $date_directory = file_build_uri($base_dir . '/' . $date);
  $statistics     = array();

  // Check to be sure that this is a real directory.
  if (file_exists($date_directory)) {
    $statistics = array();
    $statistics['users']['creation']['count'] = 0;

    // Set mask to match all files and folders.
    $mask = '/./';
    if ($contents = array_keys(file_scan_directory($date_directory, $mask))) {
      foreach ($contents as $file_uri) {
        list($data_dir, $date, $hour, $filename) = explode('/', file_uri_target($file_uri));
        $day = array_pop(explode('/', $date_directory));
        $data = _petitions_stats_users_load_data_file($file_uri);

        // If this date has not been populated, create stub.
        if (!isset($statistics['users']['creation']['dates'])) {
          $statistics['users']['creation']['dates'][$date] = array(
            'title' => $date,
            'count' => 0,
          );
        }

        // If this hour has not been populated, create stub.
        if (!isset($statistics['users']['creation']['dates'][$date]['hours'][$hour])) {
          $statistics['users']['creation']['dates'][$date]['hours'][$hour] = array(
            'title' => $hour,
            'count' => 0,
          );
        }

        // The user count for this particular data file.
        $user_count = count($data);

        // Increment totals for this hour and this day.
        $statistics['users']['creation']['dates'][$day]['hours'][$hour]['count'] += $user_count;
        $statistics['users']['creation']['dates'][$day]['count'] += $user_count;
        $statistics['users']['creation']['count'] += $user_count;
      }
    }

    // Calculate percentages.
    foreach ($statistics['users']['creation']['dates'] as $date => $date_data) {
      ksort($statistics['users']['creation']['dates'][$date]['hours']);
      foreach ($date_data['hours'] as $hour => $hour_data) {
        $percentage = ($hour_data['count'] / $date_data['count']) * 100;
        $statistics['users']['creation']['dates'][$date]['hours'][$hour]['percentage'] = $percentage;
      }
    }

    $vars = array(
      'date' => $date,
      'statistics' => $statistics,
    );

    drupal_add_css(drupal_get_path('module', 'petitions_stats_users') . '/theme/petitions_stats_users.css');
    $output .= theme('petitions_stats_users', $vars);
  }
  else {
    $output .= t('There are no user creation statistics for @date', array('@date' => $date));
  }
  return $output;
}

/**
 * Form callback for date picker on users statistics page.
 *
 * @param string $date
 *   A date in the form yyyy-mm-dd.
 *
 * @param string $format
 *   The date format of $date, as accepted by PHP's date() function.
 */
function petitions_stats_users_date_form($form, $form_state, $date, $format) {
  module_load_include('inc', 'date', 'date_api_elements');
  $form = array();

  // See other available attributes and what they do in date_api_elements.inc
  $form['date'] = array(
    '#title' => t('Select Date'),
    '#type' => 'date_select',
    '#default_value' => $date,
    '#date_format' => $format,
    '#date_year_range' => '-3:+3',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go to date'),
  );

  return $form;
}

/**
 * Submit callback for petitions_stats_users_date_form().
 */
function petitions_stats_users_date_form_submit($form, &$form_state) {
  $date = $form_state['values']['date'];
  drupal_goto('admin/people/stats/' . $date);
}

/**
 * Page callback for administrative page.
 */
function petitions_stats_users_admin_form() {
  $form = array();

  // This module was initially built to control file size directly. E.g., by
  // imposing a 1MB limit on data files. However, that method of control made
  // it very difficult to incrementally increase or decrease the contents of
  // a data file efficiently. By controlling the array size of the JSON
  // contents, we have more granular control.
  $form['psu_max_array_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum array size per data file'),
    '#description' => t('The maximum number of array rows that may be stored in a single data file. This indirectly controls the maximum size of the data file, which can have performance ramifications.'),
    '#default_value' => variable_get('psu_max_array_size', '10000'),
  );
  $form['psu_data_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Data directory'),
    '#description' => t('This is the directory in which JSON files will be stored. Enter a directory name relative to the Drupal files directory. Do not include trailing slashes.'),
    '#default_value' => variable_get('psu_data_dir', 'petitions_stats_users_data'),
  );
  $form['psu_request_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Request URL'),
    '#description' => t('The Petitions API URL to which the request will be made. Do not include parameters.'),
    '#default_value' => variable_get('psu_request_url', 'http://petitions.whitehouse.gov/api/v1/users.json'),
  );
  $form['psu_batch_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Batch size'),
    '#description' => t('Batch size for Petitions API requests. For example, a batch size of 100 and a total result count of 1000 would generate 10 requests for 100 items.'),
    '#default_value' => variable_get('psu_batch_size', 100),
  );

  return system_settings_form($form);
}

/**
 * Validation callback for petitions_stats_users_admin_form().
 */
function petitions_stats_users_admin_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!ctype_digit($values['psu_max_array_size']) || $values['psu_max_array_size'] < 1) {
    form_set_error('psu_max_array_size', t('Max array size must be a positive integer.'));
  }
  if (!valid_url($values['psu_request_url'])) {
    form_set_error('psu_request_url', t('Please enter a valid URL.'));
  }
  if (!ctype_digit($values['psu_batch_size']) || $values['psu_batch_size'] < 1) {
    form_set_error('psu_batch_size', t('Batch size must be a positive integer.'));
  }
}
