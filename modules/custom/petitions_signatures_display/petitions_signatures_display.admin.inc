<?php

/**
 * @file
 * This file provides an administration form for Petitions Signatures Display.
 */

/**
 * Menu callback for configuration form (admin/config/petitions/signatures).
 */
function petitions_signatures_display_configure() {
  $display = array(
    0 => t('First Name, Last Initial'),
    1 => t('First Initial, Last Initial'),
  );

  $form['petitions_signatures_display_initials'] = array(
    '#type' => 'radios',
    '#title' => t('Signature display options'),
    '#description' => t('Select the manner in which to display names on all
      lists of signatures. <em>Applies to all Petitions</em>.'),
    '#options' => $display,
    '#default_value' => variable_get('petitions_signatures_display_initials', 0),
  );

  return system_settings_form($form);
}
