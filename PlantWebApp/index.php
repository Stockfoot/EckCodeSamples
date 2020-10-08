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
			<h1 class = "display-4">Plants</h1>
		</div>
		<hr>
	</div>
</div>



<?php
	require "config.php";
    require "common.php";
?>

<?php
/***********************************************
 * Use an HTML form to create a new entry in the
 * plants table.
 ***********************************************/
if (isset($_POST['submit'])) 
{
    
    try  {
        $connection = new PDO($dsn, $username, $password, $options);
        
        $new_plant = array(
            "genus" 			=> $_POST['genus'],
            "species"  			=> $_POST['species'],
            "common_name"    	=> $_POST['common_name'],
            "required_light" 	=> $_POST['required_light'],
            "climate_type"  	=> $_POST['climate_type']
        );

        $sql = sprintf(
                "INSERT INTO %s (%s) values (%s)",
                "plants",
                implode(", ", array_keys($new_plant)),
                ":" . implode(", :", array_keys($new_plant))
        );
        
        $statement = $connection->prepare($sql);
        $statement->execute($new_plant);
    } 

    catch(PDOException $error)
    {
        echo $sql . "<br>" . $error->getMessage();
    }
}
?>

<!-- Select the whole table -->
<?php
 		
        $connection = new PDO($dsn, $username, $password, $options);
        $sql = "SELECT * FROM plants";
 
        $statement = $connection->prepare($sql);
        $statement->execute();
        $result = $statement->fetchAll();
?>


<!--Add New Plant Form-->
<div class = "container-fluid form-group contactForm">
<form id = "plantForm" name = "newPlant" method = "post" role="form" class="form-horizontal" >
    <fieldset>
        <legend>Enter a new plant.</legend>
        <hr>
            
        <label>Genus
        	<br/>
            <input type = "text" class = "submissionField" name = "genus"  id = "genus" size = "20" maxlength = "50" placeholder = "Required String" required>
       	</label>

      	<label>Species
        	<br/>
            <input type = "text" class = "submissionField" name = "species" id = "species" size = "20" maxlength = "50" placeholder = "Required String" required>
       	</label>

       <label>Common Name
        	<br/>
            <input type = "text" class = "submissionField" name = "common_name" id = "common_name" size = "20" maxlength = "50" placeholder = " Optional String">
       	</label>

       	<label>Required Light
        	<br/>
        	<?php 
           		$connection = new PDO($dsn, $username, $password, $options);
        		$sql = "SELECT id AS required_light, sunlight_hours FROM sunlight";
        		$statement = $connection->prepare($sql);
				$statement->execute();
				$lights = $statement->fetchAll();
			?>
            <select name = "required_light" id = "required_light">
            	<?php foreach($lights as $light): ?>
        		<option value="<?= $light['required_light']; ?>"><?= $light['required_light']; ?>. <?= $light['sunlight_hours']; ?> Sunlight Hours</option>
    			<?php endforeach; ?>
            </select>
       	</label>

       	<label>Climate Type
        	<br/>
        	<?php 
           		$connection = new PDO($dsn, $username, $password, $options);
        		$sql = "SELECT id AS climate_type, lowest_temperature, highest_temperature FROM climate";
        		$statement = $connection->prepare($sql);
				$statement->execute();
				$climates = $statement->fetchAll();
			?>
            <select name = "climate_type" id = "climate_type">
            	<?php foreach($climates as $climate): ?>
        		<option value="<?= $climate['climate_type']; ?>"><?= $climate['climate_type']; ?>. <?= $climate['lowest_temperature']; ?> - <?= $climate['highest_temperature']; ?> degrees</option>
    			<?php endforeach; ?>
            </select>
       	</label>

        <input type = "submit" name = "submit" value = "Submit" />
            
    </fieldset>
</form>

<br/>

<br/>

</div>
<hr>
<br/>





<!-- Delete a row from table -->
<?php

$success = null;
if (isset($_POST["delete"])) {
  
if(!function_exists('hash_equals'))
{
    function hash_equals($str1, $str2)
    {
        if(strlen($str1) != strlen($str2))
        {
            return false;
        }
        else
        {
            $res = $str1 ^ $str2;
            $ret = 0;
            for($i = strlen($res) - 1; $i >= 0; $i--)
            {
                $ret |= ord($res[$i]);
            }
            return !$ret;
        }
    }
}

  if (!hash_equals($_SESSION['csrf'], $_POST['csrf'])) die();
  try {
    $connection = new PDO($dsn, $username, $password, $options);
  
    $id = $_POST["delete"];
    $sql = "DELETE FROM plants WHERE id = :id";
    $statement = $connection->prepare($sql);
    $statement->bindValue(':id', $id);
    $statement->execute();
    $success = "User successfully deleted";
  } catch(PDOException $error) {
    echo $sql . "<br>" . $error->getMessage();
  }
}
try {
  $connection = new PDO($dsn, $username, $password, $options);
  $sql = "SELECT * FROM plants";
  $statement = $connection->prepare($sql);
  $statement->execute();
  $result = $statement->fetchAll();
} catch(PDOException $error) {
  echo $sql . "<br>" . $error->getMessage();
}
?>






<!--Table Section-->
<br/>
<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			<h1 class = "display-4">Display the plant table.</h1>
		<hr>

		<form method = "post">
		<input name="csrf" type="hidden" value="<?php echo escape($_SESSION['csrf']); ?>">
		<table style = "width:100%">
			<tr>
				<th>ID</th>
				<th>Genus</th>
				<th>Species</th>
				<th>Common Name</th>
				<th>Required Light</th>
				<th>Climate Type</th>
				<th>Update</th>
				<th>Delete</th>
			</tr>



		<?php foreach ($result as $row) { ?>
            <tr>
                <td><?php echo escape($row["id"]); ?></td>
                <td><?php echo escape($row["genus"]); ?></td>
                <td><?php echo escape($row["species"]); ?></td>
                <td><?php echo escape($row["common_name"]); ?></td>
                <td><?php echo escape($row["required_light"]); ?></td>
                <td><?php echo escape($row["climate_type"]); ?></td>
                <td><a href="updateplant.php?id=<?php echo escape($row["id"]); ?>">UPDATE</a></td>
				<td>
					<button type="submit" name="delete" class="btn" value="<?php echo escape($row["id"]); ?>">DELETE</button>
				</td>

            </tr>
        <?php } ?>


		</table>
	</form>

	</div>
</div>

<hr>
<br/>
</div>

<!-- Unique Tables to Display-->

<div class = "container-fluid form-group contactForm">
<form action="search.php" method="GET">
<fieldset>
        <legend>Search For a Plant By Genus, Species, or Common Name</legend>
        <hr>
    <input type="text" name="query" />
    <input type="submit" value="Search" />
    <hr>
</fieldset>
</form>
</div>
<hr>





<!-- Filter Dropdown Query Section -->
<!-- Select the whole table -->
<?php
 	if (isset($_POST["filter"]))
 	{ 
       	$connection = new PDO($dsn, $username, $password, $options);
        $filter = $_POST['filter'];

        switch($filter)
        {
        	case "highTemperature": 
        		$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM climate, plants
				WHERE climate.id = plants.climate_type
				AND highest_temperature > 90";
				break;

			case "lowTemperature": 
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM climate, plants
				WHERE climate.id = plants.climate_type
				AND lowest_temperature < 20";
				break;

			case "lowLight":
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM sunlight, plants
				WHERE sunlight.id = plants.required_light
				AND low_sunlight = 1
				AND full_sunlight = 0";
				break;

			case "fullLight":
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM sunlight, plants
				WHERE sunlight.id = plants.required_light
				AND low_sunlight = 0
				AND full_sunlight = 1";
				break;

			case "waterDaily":
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM watering_cycle, plants_watering, plants
				WHERE watering_cycle.id = plants_watering.watering_id
				AND plants_watering.plant_id = plants.id
				AND days = 0";
				break;

			case "waterWeekly":
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM watering_cycle, plants_watering, plants
				WHERE watering_cycle.id = plants_watering.watering_id
				AND plants_watering.plant_id = plants.id
				AND days > 7";
				break;

			case "acidicSoil":
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM soil, plants_soil, plants
				WHERE soil.id = plants_soil.soil_id
				AND plants_soil.plant_id = plants.id
				AND soil_ph <= 7";
				break;

			case "basicSoil":
				$sql = "SELECT plants.genus, plants.species, plants.common_name
				FROM soil, plants_soil, plants
				WHERE soil.id = plants_soil.soil_id
				AND plants_soil.plant_id = plants.id
				AND soil_ph > 7";
				break;
        }

        
        $statement = $connection->prepare($sql);
        $statement->execute();
        $filter = $statement->fetchAll();
    }
?>


<div class = "container-fluid form-group contactForm">
<form method="POST" action="index.php">
	<fieldset>
        <legend>Filter Results</legend>
        <hr>
        
            <div class="search-box">
                <select name = "filter">
                    <option value = "highTemperature">Display high temperature tolerant plants</option>
                    <option value = "lowTemperature">Display low temperature tolerant plants</option>
                    <option value = "lowLight">Display low light tolerant plants</option>
                    <option value = "fullLight">Display medium to full light tolerant plants</option>
                    <option value = "waterDaily">Display plants that need to be watered daily</option>
                    <option value = "waterWeekly">Display plants that need to be watered less frequently</option>
                    <option value = "acidicSoil">Display plants that prefer acidic soil</option>
                    <option value = "basicSoil">Display plants that prefer basic soil</option>
                </select>
                <br/>
                <br/>
                <button id="filter">Search</button>
            
           </div>
        
    </fieldset>
    </form>
</div>

<!-- Table to display filtered results -->
<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			<h1>Filtered Results</h1>
		<hr>
		<table style = "width:100%">
			<tr>
				<th>Genus</th>
				<th>Species</th>
				<th>Common Name</th>
			</tr>



		<?php 
		if (isset($_POST["filter"])) {
			foreach ($filter as $row) { ?>
            <tr>
                <td><?php echo escape($row["genus"]); ?></td>
                <td><?php echo escape($row["species"]); ?></td>
                <td><?php echo escape($row["common_name"]); ?></td>
            </tr>
        
        <?php } } ?>


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

