<?php

/**
 * @file
 * Hooks provided by Simple Togle.
 */

/**
 * Provide information about toggles.
 */
function hook_simple_toggle_info() {
  $toggle_info = array();

  // Toggles are grouped by module.
  $toggle_info['simple_toggle'] = array();

  // Each toggle has a machine_name as the key, and the default state as value.
  $toggle_info['simple_toggle']['first_toggle'] = array(
    'title' => "Activate awesomeness", 'default_state' => 1);

  $toggle_info['simple_toggle']['second_toggle'] = array(
    'title' => "Activate less awesomeness", 'default_state' => 0);

  return $toggle_info;
}
