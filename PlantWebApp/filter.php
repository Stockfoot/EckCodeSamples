<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>The Plant Database (Group 13)</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
	<link href="https://fonts.googleapis.com/css?family=Montserrat" rel="stylesheet"> 
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.2/css/all.css" integrity="sha384-oS3vJWv+0UjzBfQzYUhtDYW+Pj2yciDJxpsK1OYPAYjqT085Qq/1cq5FLXAZQ7Ay" crossorigin="anonymous">
	<link href="style.css" rel="stylesheet">
</head>

<body>



<!--Navigation Bar-->
<nav class = "navbar navbar-expand-md navbar-light bg-light sticky-top">
	
	<!--Takes up 100% of the screen-->
	<div class = "container-fluid">
		
		<!--Logo-->
		<a class = "navbar-brand" href = "index.php"><img src = "img/logo.png"></a>
		
		<!--Navbar collapses to a button for mobile or small screens-->
		<button class = "navbar-toggler" type = "button" data-toggle = "collapse" data-target = "#navbarResponsive">
			<span class ="navbar-toggler-icon"></span>
		</button>
		
		<!--Navbar links to other pages-->
		<div class = "collapse navbar-collapse" id = "navbarResponsive">
			
			<!--Unordered list used for navbar titles and links-->
			<ul class = "navbar-nav ml-auto">
				<li class = "nav-item active">
					<a class = "nav-link" href="index.php">PLANTS</a>
				</li>
				<li class = "nav-item">
					<a class = "nav-link" href="climate.php">CLIMATE</a>
				</li>
				<li class = "nav-item">
					<a class = "nav-link" href="sunlight.php">SUNLIGHT</a>
				</li>
				<li class = "nav-item">
					<a class = "nav-link" href="soil.php">SOIL</a>
				</li>
				<li class = "nav-item">
					<a class = "nav-link" href="wateringcycle.php">WATERING CYCLE</a>
				</li>
				<li class = "nav-item">
					<a class = "nav-link" href="intermediatetables.php">INTERMEDIATE TABLES</a>
				</li>

			</ul>
		</div>

	</div> 
</nav>

<!--Welcome Section-->
<br/>
<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			<h1 class = "display-4">Your Filtered Results</h1>
		</div>
		<hr>
	</div>
</div>



<?php
	require "config.php";
    require "common.php";
?>

<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			
		<hr>
		<table style = "width:100%">
			<tr>
				<th>Genus</th>
				<th>Species</th>
				<th>Common Name</th>
			</tr>



		<?php foreach ($filter as $row) { ?>
            <tr>
                <td><?php echo escape($row["genus"]); ?></td>
                <td><?php echo escape($row["species"]); ?></td>
                <td><?php echo escape($row["common_name"]); ?></td>
            </tr>

        <?php } ?>


		</table>
</div>
</div>
</div>


<!--Footer-->
<br/>
<br/>
<footer>
	<div class = "container-fluid padding text-center">
		
			
			<h3><i class="fas fa-seedling"></i>Russell Eck and Morgan Eck</h3>
			

		
	</div>
</footer>


</body>
</html>