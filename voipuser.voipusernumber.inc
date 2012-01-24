<?php

/**
 * @file
 *   VoipUserNumber class file.
 */

/**
 * Unique VoIP User Number's instance of VoIP Number.
 *
 * This may add confusion but: (better way?)
 *
 * Static methods remain from parent, although those based
 * on a node context aren't relevant here. Parent methods
 * will return a VoipNumber.
 *
 * Additional status handling for VoIP User number types
 * required and added.
 *
 * To keep in line with database naming internal variables
 * are different as well. Allows for just saving object,
 * but...
 */
class VoipUserNumber extends VoipNumber {
  public $phone;
  public $uid;
  public $number_prefix;
  public $status;

  /**
   * Construct from arguments.
   *
   * @param string $phone
   *   Phone number.
   * @param string $uid
   *   Name of number. Here just use uid.
   * @param string $number_prefix
   *   Type, or prefex, of the number. Usually unknown. @todo confirm.
   * @param int $status
   *   VoIP User Number status.
   */
  function __construct($phone, $uid, $number_prefix, $status) {
    $this->phone = $phone;
    $this->uid = $uid;
    $this->number_prefix = $number_prefix;
    $this->status = $status;
  }

  /**
   * Return unique id for a VoipUserNumber.
   *
   * This is specific to this module, so no hook, but database prodding.
   * Breaking the model of the parent object again.
   *
   * @param int|string $number
   *   Number to look up.
   *
   * @return int|bool
   *   User ID. FALSE if none.
   */
  public static function getUidFromNumber($number) {
    return db_result(db_query("SELECT uid FROM {voipuser_numbers} WHERE phone = '%s'", $number));
  }

  /**
   * Override get node id as it makes no sense in this context.
   */
  public function getNid() {
    return FALSE;
  }

  /**
   * Override get name, as we're using UID.
   */
  public function getName() {
    return $this->uid;
  }

  /**
   * Override get number.
   *
   * @todo could move schema to use 'number' rather than phone.
   */
  public function getNumber() {
    return $this->phone;
  }

  /**
   * Make number in/active.
   *
   * @param bool $active
   *   TRUE active; FALSE inactive.
   */
  public function setActive($active) {
    if ($active) {
      $this->status = $this->status | VOIPUSER_NUMBER_ACTIVE;
    }
    else {
      $this->status = $this->status ^ VOIPUSER_NUMBER_ACTIVE;
    }
  }

  /**
   * Make number un/confirmed.
   *
   * @param bool $confirmed
   *   (optional) TRUE confirmed, default; FALSE unconfirmed.
   */
  public function setConfirmed($confirmed = TRUE) {
    if ($confirmed) {
      $this->status = $this->status | VOIPUSER_NUMBER_CONFIRMED;
    }
    else {
      $this->status = $this->status ^ VOIPUSER_NUMBER_CONFIRMED;
    }
  }

  /**
   * Make number (not) default.
   *
   * NOTE at the moment this isn't handling removing default
   * status from any other numbers attached to this uid.
   *
   * @param bool $default
   *   (optional) TRUE default, default; FALSE not default.
   */
  public function setDefault($default) {
    if ($default) {
      $this->status = $this->status | VOIPUSER_NUMBER_DEFAULT;
    }
    else {
      $this->status = $this->status ^ VOIPUSER_NUMBER_DEFAULT;
    }
  }

  /**
   * Get active status.
   *
   * @return bool
   *   TRUE if active.
   */
  public function getActive() {
    return (bool) $this->status & VOIPUSER_NUMBER_ACTIVE;
  }

  /**
   * Get confirmed status.
   *
   * @return bool
   *   TRUE if confirmed.
   */
  public function getConfirmed() {
    return (bool) $this->status & VOIPUSER_NUMBER_CONFIRMED;
  }

  /**
   * Get default status.
   *
   * @return bool
   *   TRUE if this is a default number.
   */
  public function getDefault() {
    return (bool) $this->status & VOIPUSER_NUMBER_DEFAULT;
  }
}
