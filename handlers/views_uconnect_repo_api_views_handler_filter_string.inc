<?php

/**
 * @file
 * Definition of views_handler_filter_string.
 */

/**
 * Basic textfield filter to handle string filtering commands
 * including equality, like, not like, etc.
 *
 * @ingroup views_filter_handlers
 */
class views_uconnect_repo_api_views_handler_filter_string extends views_handler_filter_string {
  function query() {
	$this->field_alias = $this->real_field;
  }
}
