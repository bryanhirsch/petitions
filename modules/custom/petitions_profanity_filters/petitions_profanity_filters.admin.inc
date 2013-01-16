<?php

/**
 * @file
 * This file provides an administration form for Petitions Profanity Filters.
 */

/**
 * Menu callback for configuration form (admin/config/petitions/profanity).
 */
function petitions_profanity_filters_configure() {
  $form['petitions_profanity_filters_initials'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display first and last initials only?'),
    '#description' => t('Select to display only the first and last initials of
      names on all lists of signatures. <em>Applies to all Petitions</em>.'),
    '#default_value' => variable_get('petitions_profanity_filters_initials', 0),
  );
  return system_settings_form($form);
}
