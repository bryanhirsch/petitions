<?php
/**
 * Act when a petition has been saved to MongoDB.
 *
 * @param array $petition
 *  an array with the petition's data.
 */
function hook_wh_petitions_petition_save($petition){
}

/**
 * Act when a petition has been closed.
 *
 * @param array $petition
 *   an array with the petition's data.
 */
function hook_wh_petitions_petition_close($petition){
}

/**
 * Act when the body of a petition has been updated.
 *
 * @param array $petition
 *   an array with the petition's data.
 */
function hook_wh_petitions_petition_body_update($petition){
}

/**
 * Act when a petition is being flagged as innappropirate.
 *
 * @param string $petition_id
 *   The petition's identifier.
 */
function hook_wh_petitions_petition_inappropriate($petition_id){
}


