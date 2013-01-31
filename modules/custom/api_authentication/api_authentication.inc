<?php

/**
 * @file
 * Include file for api_authentication module.
 */

/**
 * Authenticates a call using a key to verify the request.
 */
function _api_authentication_authenticate_call($settings, $method, $args) {
  $request = getallheaders();
  $key = $request['Key'];
  $authkey = variable_get('api_authentication_key', '');
  if ($key != $authkey) {
    return services_error(t('You do not have permission to access this resource.'), 401);
  }
}
