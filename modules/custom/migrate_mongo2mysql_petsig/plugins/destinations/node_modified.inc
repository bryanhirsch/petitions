<?php

/**
 * @file
 * Support for node destinations.
 */

class MigrateDestinationNodeModified extends MigrateDestinationNode {

  /**
   * Overloading prepare method.
   */
  public function prepare($entity, stdClass $source_row) {
    parent::prepare($entity, $source_row);

    // Let's check the title for unsupported chars.
    $entity->title = $this->replace4byte($entity->title);

    // Let's check the body for unsupported chars.
    $entity->body[LANGUAGE_NONE][0]['value'] = $this->replace4byte(
      $entity->body[LANGUAGE_NONE][0]['value']);

  }

  /**
   * Replace 4-byte utf8 chars with an undefined symbol.
   *
   * @param string $string
   *   A string.
   *
   * @return string
   *   the string without 4 byte utf8 chars.
   */
  public function replace4byte($string) {
    return preg_replace('%(?:
          \xF0[\x90-\xBF][\x80-\xBF]{2}      # planes 1-3
        | [\xF1-\xF3][\x80-\xBF]{3}          # planes 4-15
        | \xF4[\x80-\x8F][\x80-\xBF]{2}      # plane 16
      )%xs', "�", $string);
  }
}
