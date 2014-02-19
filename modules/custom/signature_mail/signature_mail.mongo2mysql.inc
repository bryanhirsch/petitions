<?php
/**
 * @file
 * Separete anything related to our MongoDB to MySQL transition.
 */

/**
 * Get the input from what is saved to mongodb transform it and save it.
 *
 * @param array $mongodb_signature
 *   An array of data as it is structure when loaded from MongoDB.
 */
function signature_mail_mongodb_save($mongodb_signature) {
  // Turn _id into the legacy_id.
  $_id = $mongodb_signature['_id']->__toString();
  unset($mongodb_signature['_id']);
  $mongodb_signature['legacy_id'] = $_id;

  // Turn the mongodb petition id, into the legacy_petition_id.
  $petition_id = $mongodb_signature['petition_id'];
  unset($mongodb_signature['petition_id']);
  $mongodb_signature['legacy_petition_id'] = $petition_id;

  // Let's get the node id of the petition.
  $node = petition_load_from_legacy_id($petition_id);
  if ($node) {
    $mongodb_signature['petition_id'] = $node->nid;
  }

  $user = $mongodb_signature['user'];
  unset($mongodb_signature['user']);

  foreach ($user as $property => $value) {
    $pn = "user_" . $property;
    $mongodb_signature[$pn] = $value;
  }

  // Let's double check that we have default values for all properties.
  $schema = drupal_get_schema("signature_mail");
  foreach ($schema['fields'] as $property => $info) {
    if (empty($mongodb_signature[$property])) {
      if ($property != 'id' && ($info['type'] == 'text' ||
              $info['type'] == "varchar")) {
        $mongodb_signature[$property] = "";
      }
      elseif ($property != 'id' && $info['type'] == 'int') {
        $mongodb_signature[$property] = 0;
      }
    }
  }

  $signature = entity_create("signature_mail", $mongodb_signature);
  $signature->save();
}
