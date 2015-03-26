<?php
/**
 * @file
 *   Views field handler
 */

/**
 * Views field handler
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class views_uconnect_repo_api_handler_field_prerender_list extends views_handler_field_prerender_list {

	function query() {

		$this -> field_alias = $this -> real_field;
	}

	function pre_render(&$values) {
	}


	/**
	 * Need to get this checked, not sure if this is the correct way to do this.
	 */
	function advanced_render($values) {
		if($this->real_field == 'edLevel'){
			// if working with edLevel
			$items = $values -> items -> edLevel;
		} else if($this->real_field == 'subject'){
			// if working with edLevel
			$items = $values -> items -> subject;
			if(is_array($items)){
				sort($items);
			}
		} else if($this->real_field == 'type'){
			// if working with type
			$items = $values -> items -> type;
			
			if(is_array($items)){
				sort($items);
			}
		} else if($this->real_field == 'standard'){
			// if working with type
			$items = $values -> items -> standard;
			
			if(is_array($items)){
				sort($items);
			}
		} else if($this->real_field == 'collection'){
			// if working with type
			$items = $values -> items -> collection;
			if(is_array($items)){
				sort($items);
			}
		} else if($this->real_field == 'edLevel_filter'){
			// if working with edLevel
			if(isset($values -> items -> edLevel_filter)){
				$items = $values -> items -> edLevel_filter;
			}
		} else if($this->real_field == 'subject_filter'){
			// if working with edLevel
			if(isset($values -> items -> subject_filter)){
				$items = $values -> items -> subject_filter;
				if(is_array($items)){
					sort($items);
				}
			}
		} else if($this->real_field == 'type_filter'){
			// if working with type
			if(isset($values -> items -> type_filter)){
				$items = $values -> items -> type_filter;
				if(is_array($items)){
					sort($items);
				}
			}
		} else if($this->real_field == 'collection_filter'){
			// if working with type
			if(isset($values -> items -> collection_filter)){
				$items = $values -> items -> collection_filter;
				if(is_array($items)){
					sort($items);
				}
			}
		}
		
		
		if (!empty($items)) {
			if ($this -> options['type'] == 'separator') {
				return implode($this -> sanitize_value($this -> options['separator'], 'xss_admin'), $items);
			} else {
				return theme('item_list', array('items' => $items, 'title' => NULL, 'type' => $this -> options['type'], ));
			}
		}

	}

}
