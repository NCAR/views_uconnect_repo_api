<a href="<?php echo $url;?>"><?php echo $url;?></a><br/>
<?php if(!empty($img)){?>
<p style="float:right"><img src="<?php echo $img; ?>"/></p>
<?php } ?>
<p><?php echo $description;?></p>
<div style="clear:both;"></div>
<table class="views_uconnect_repo_api_search_item">
	<?php if(!empty($educationLevel)){?>
	<tr>
		<th>Education Level</th>
		<td><?php echo $educationLevel;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($subject)){?>
	<tr>
		<th>Subject</th>
		<td><?php echo $subject;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($type)){?>
	<tr>
		<th>Resource Type</th>
		<td><?php echo $type;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($format)){?>
	<tr>
		<th>Format</th>
		<td><?php echo $format;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($language)){?>
	<tr>
		<th>Language</th>
		<td><?php echo $language;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($creator)){?>
	<tr>
		<th>Creator</th>
		<td><?php echo $creator;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($license)){?>
	<tr>
		<th>License</th>
		<td><?php echo $license;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($accessRights)){?>
	<tr>
		<th>Access Rights</th>
		<td><?php echo $accessRights;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($rights)){?>
	<tr>
		<th>Rights</th>
		<td><?php echo $rights;?></td>
	</tr>
	<?php } ?>
	<?php if(!empty($conformsTo)){?>
	<tr>
		<th>Standards</th>
		<td><?php echo $conformsTo;?></td>
	</tr>
	<?php } ?>
</table>
<?php


