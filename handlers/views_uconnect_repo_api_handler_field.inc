<?php
/**
* @file
*   Views field handler
*/

/**
* Views field handler
*
* The only thing we're doing here is making sure the field_alias
* gets set properly, and that none of the sql-specific query functionality
* gets called.
*/
class views_uconnect_repo_api_handler_field extends views_handler_field {
  function query() {
    $this->field_alias = $this->real_field;
  }
}