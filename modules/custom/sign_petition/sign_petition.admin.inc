<?php

/**
 * @file
 * Provides admin settings for sign_petition module.
 */

/**
 * Configuration for sign petition module.
 *
 * @see system_settings_form()
 */
function sign_petition_configure() {
  $form = array();

  $form['sign_petition_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('API base URL'),
    '#description' => t('Base URL (e.g. https://api.whitehouse.gov/v1)'),
    '#default_value' => variable_get('sign_petition_base_url'),
  );
  $form['sign_petition_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#description' => t('API key from the Petitions site.'),
    '#default_value' => variable_get('sign_petition_api_key'),
  );
  $form['sign_petition_petition_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Petition ID'),
    '#default_value' => variable_get('sign_petition_petition_id'),
  );

  return system_settings_form($form);
}
