<?php

/**
 * Allow modules to process the signature data.
 *
 * @param array $item
 *   the signture data.
 * @param object $user
 *   user data.
 *
 * @return string
 *   the signature id.
 */
function hook_signtures_queue_signature_process($item, $user){
  // Do something with the signature data.
}

/**
 * Allow modules to use the signature data after it has been processed.
 *
 * @param array $item
 *   the signture data
 * @param object $user
 *   user data
 */
function hook_signtures_queue_signature_post_process($item, $user){
  // Do something with the signature data.
}
