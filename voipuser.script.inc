<?php

/**
 * @file
 *   Default VoIP scripts for interecting with VoIP user.
 */

/**
 * Automatically log in dialled-in user, by telephone number.
 *
 * @param string $number
 *   Phone number. For example from the script %caller_number variable.
 * @param bool $create
 *   (optional) If number is not known create a new user. Default FALSE.
 */
function voipuser_autologin_script($number, $create = FALSE) {
  $uid = VoipUserNumber::getUidFromNumber($number);
  if ($uid) {
    // Add to session.
    return $uid;
  }
  elseif ($create) {
    // Create new user.
    return $uid;
  }

  return FALSE;
}

