<?php
/**
 * Implementation of hook_views_plugins().
 */
function views_uconnect_repo_api_views_plugins() {
	$plugin = array();
	$plugin['query']['views_uconnect_repo_api_plugin_query'] = array(
		'title' => t('UCARConnect Repository API Query'), 
		'help' => t('UCARConnect Repository API query object.'), 
		'handler' => 'views_uconnect_repo_api_plugin_query', 
	);
	return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function views_uconnect_repo_api_views_data() {
	$data = array();

	// Base data
	$data['views_uconnect_repo_api']['table']['group'] = t('UCARConnect API Groups');
	$data['views_uconnect_repo_api']['table']['base'] = array(
		'title' => t('UCARConnect Repository API'), 
		'help' => t('Query UCARConnect Repository API.'), 
		'query class' => 'views_uconnect_repo_api_plugin_query'
	);

	// Fields
	
	// for title
	$data['views_uconnect_repo_api']['title'] = array(
		'title' => t('Title'), 
		'help' => t('The title of this resource.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field', 
      		'click sortable' => TRUE,
		), 
	);
	
	 // for description
	$data['views_uconnect_repo_api']['description'] = array(
		'title' => t('Description'), 
		'help' => t('The description of the resource.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field', 
		), 
	);
	
	 // for id
	$data['views_uconnect_repo_api']['id'] = array(
		'title' => t('ID'), 
		'help' => t('The ID of the resource.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field', 
		), 
	);
	
	// for url
	$data['views_uconnect_repo_api']['url'] = array(
		'title' => t('URL'), 
		'help' => t('The URL of the resource.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_url', 
		), 
	);
	
	// for education level
	$data['views_uconnect_repo_api']['edLevel'] = array(
		'title' => t('Education Level'), 
		'help' => t('The education levels this resource is for.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		),
	);
	
	// for education level filter
	$data['views_uconnect_repo_api']['edLevel_filter'] = array(
		'title' => t('Education Level from filter'), 
		'help' => t('The education levels filters the user selected.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
    	'filter' => array(
      		'handler' => 'views_uconnect_repo_api_handler_filter_in_operator_education_level',
      		'label' => t('Education Level'),
    	),
	);
	
	// for subject 
	$data['views_uconnect_repo_api']['subject'] = array(
		'title' => t('Subject'), 
		'help' => t('The subject this resource covers.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
	);
	
	// for subject filter
	$data['views_uconnect_repo_api']['subject_filter'] = array(
		'title' => t('Subject from filter'), 
		'help' => t('The subject filters the user selected.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
    	'filter' => array(
      		'handler' => 'views_uconnect_repo_api_handler_filter_in_operator_subject',
      		'label' => t('Subject'),
    	),
	);
	
	// for resource type
	$data['views_uconnect_repo_api']['type'] = array(
		'title' => t('Resource type'), 
		'help' => t('The type of resource this resource is.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
	);
	
	// for resource type filter
	$data['views_uconnect_repo_api']['type_filter'] = array(
		'title' => t('Type from filter'), 
		'help' => t('The type filters the user selected.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
    	'filter' => array(
      		'handler' => 'views_uconnect_repo_api_handler_filter_in_operator_resource_type',
      		'label' => t('Resource Type'),
    	),
	);
	
	
	// for standard
	$data['views_uconnect_repo_api']['standard'] = array(
		'title' => t('Standard'), 
		'help' => t('The aligned educational standard.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
	);
	
	// for collection
	$data['views_uconnect_repo_api']['collection'] = array(
		'title' => t('Collection'), 
		'help' => t('The collection this resource belongs to.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
	);
	
	// for collection filter
	$data['views_uconnect_repo_api']['collection_filter'] = array(
		'title' => t('Collection from filter'), 
		'help' => t('The collection filters the user selected.'), 
		'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field_prerender_list', 
		), 
    	'filter' => array(
      		'handler' => 'views_uconnect_repo_api_handler_filter_in_operator_collection',
      		'label' => t('Collection'),
    	),
	);
	
	
	
	// for search filter
	$data['views_uconnect_repo_api']['term'] = array(
    	'title' => t('Search term'),
    	'help' => t('The user provided search term'),
    	'field' => array(
			'handler' => 'views_uconnect_repo_api_handler_field', 
		), 
    	'filter' => array(
      		'handler' => 'views_uconnect_repo_api_handler_filter_string',
      		'label' => t('Search term'),
      		'use equal' => TRUE,
        	'allow empty' => TRUE,
    	),
  	);
	return $data;
}
