<?php
/**
 * @file services_documentation.admin.inc 
 */

/**
 *
 */
function services_documentation_configure() {
  $form = array();

  // Designate documentation basepath.
  $form['services_documentation_base_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Set your documentation base path here:'),
    '#default_value' => variable_get('services_documentation_base_path', 'developers'),
    '#description' => 'If you enter "developers" here, your documentation will appear at /developers/1000, /developers/2000, /developers/3000. Your documentation homepage will be /developers. If you enter "documentation", your homepage will be /documentation, and your documentation will live here: /documentation/1000, /documentation/2000, etc.',
  );

  // Designate page to use for "homepage" (at basepath).
  $form['services_documentation_homepage'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#default_value' => variable_get('services_documentation_homepage', 'hello-world'),
    '#description' => "Enter a valid Drupal path for your Services Documentation homepage. For example: node/1 or [services-documentation-base-path]/[recommended-api-version]. If you don't set anything, Services Documentation will simply present a list of links to different versions of documentation for each major API version.",
  );

  return system_settings_form($form);
}
