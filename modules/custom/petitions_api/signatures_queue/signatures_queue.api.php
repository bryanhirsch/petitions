<?php

/**
 * Allow modules to use the signature data after it has been processed.
 *
 * @param array $item
 *   the signture data
 * @param object $user
 *   user data
 */
function hook_signtures_queue_signature_post_process_alter($item, $user){
  // Do something with the signature data.
}
