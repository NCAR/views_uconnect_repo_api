UCARConnect Views Repo API
===================

## Introduction

The UCARConnect Views Repo API module is a Drupal 7 module that enables the creation of a view that searches over the UCARConnect repository.

## Requirements

This module requires the following modules/libraries:

[UCARConnect] (https://github.com/slclark/uconnect)

## Installation

Install as usual via the Drupal admin modules screen.

## Configuration

To create a view using the UCARConnect Repository API

1. Go to Admin > Structure > Views
2. Select 'add new view' 
3. Provide a View name for your new view and select UCARConnect Repository API from the 'Show' dropdown
4. Click 'Continue and edit'
5. Click the 'Add' button and select 'Page'
6. Under 'Page Settings' click 'No path is set' and define the relative URL your search results should be viewed at
7. Under 'Advanced,' click the 'settings' link next to 'Query settings' and define your repository base url.  For example: http://uc.dls.ucar.edu/search-api
8. Select your filters and fields as you normally would for a Views display.* 
9. Make additional adjustments, such as pager options or no results text, as desired.

*Note: Since this plugin queries data from the UCARConnect repository, fields are listed as UCARConnect API Groups.

## Maintainers/Sponsors

Current maintainers:

* [Sharon Clark] (https://github.com/slclark)

## Version history

Version  | NOTES
------------- | -------------
7.x-1.1  | added the new partner (UCAR) subject to display.  This still needs to be tested after resources are aligned to this new vocabulary.
