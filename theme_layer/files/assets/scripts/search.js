(function ($) {
	
	Drupal.behaviors.uconnectsearchdropdowns = {

    attach: function (context, settings) { 
    	         
		$("select").multiselect({
			   selectedText: "# of # selected",
			   selectedList: 1,
			 
			   noneSelectedText: '--All--',
			   classes: 'uconnect_search_filter',
		});
		//.multiselectfilter();
   }
   
 };
})(jQuery);
