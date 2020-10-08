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
				<li class = "nav-item">
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
				<li class = "nav-item active">
					<a class = "nav-link" href="intermediatetables.php">INTERMEDIATE TABLES</a>
				</li>

			</ul>
		</div>

	</div> 
</nav>

<?php
	require "config.php";
    require "common.php";
?>

<!--Welcome Section-->
<br/>
<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			<h1 class = "display-4">Intermediate Tables</h1>
		</div>
		<hr>
	</div>
</div>


<!--Add New Soil Connection Form-->
<div class = "container-fluid form-group contactForm">
<form id = "connectionForm" name = "newConnection" method = "post" role="form" class="form-horizontal" >
    <fieldset>
        <legend>Create A New Plant and Soil Connection</legend>
        <hr>
            
        <label>Plant Species
        	<br/>
        	<?php 
           		$connection = new PDO($dsn, $username, $password, $options);
        		$sql = "SELECT id AS plant_id, species FROM plants";
        		$statement = $connection->prepare($sql);
				$statement->execute();
				$species = $statement->fetchAll();
			?>
            <select name = "plant_id" id = "plant_id">
            	<?php foreach($species as $plant): ?>
        		<option value="<?= $plant['plant_id']; ?>"><?= $plant['plant_id']; ?>. <?= $plant['species']; ?></option>
    			<?php endforeach; ?>
            </select>
       	</label>

      	<label>Soil Type
        	<br/>
            <?php 
           		$connection = new PDO($dsn, $username, $password, $options);
        		$sql = "SELECT id AS soil_id, soil_type FROM soil";
        		$statement = $connection->prepare($sql);
				$statement->execute();
				$soils = $statement->fetchAll();
			?>
			<select name = "soil_id" id = "soil_id">
            	<?php foreach($soils as $soil): ?>
        		<option value="<?= $soil['soil_id']; ?>"><?= $soil['soil_id']; ?>. <?= $soil['soil_type']; ?></option>
    			<?php endforeach; ?>
            </select>
       	</label>

       
        <input type = "submit" name = "submitConnection" value = "Submit" />
            
    </fieldset>
</form>

<?php
if (isset($_POST['submitConnection'])) 
{
    
    try  {
        $connection = new PDO($dsn, $username, $password, $options);
        
        $new_connection = array(
            "plant_id" 			=> $_POST['plant_id'],
            "soil_id"  			=> $_POST['soil_id']
        );

        $sql = sprintf(
                "INSERT INTO %s (%s) values (%s)",
                "plants_soil",
                implode(", ", array_keys($new_connection)),
                ":" . implode(", :", array_keys($new_connection))
        );
        
        $statement = $connection->prepare($sql);
        $statement->execute($new_connection);
    } 

    catch(PDOException $error)
    {
        echo $sql . "<br>" . $error->getMessage();
    }
}
?>

<br/>
<hr>
</div>





<!-- Delete a row from table -->
<?php

$success = null;
if (isset($_POST["deletePlantsSoil"])) {
  
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
  
    $id = $_POST["deletePlantsSoil"];
    $sql = "DELETE FROM plants_soil WHERE plant_id = :plant_id";
    $statement = $connection->prepare($sql);
    $statement->bindValue(':plant_id', $id);
    $statement->execute();
    $success = "Link successfully deleted";
  } catch(PDOException $error) {
    echo $sql . "<br>" . $error->getMessage();
  }
}

?>




<!-- Select and display plant_soil table -->
<?php
 		
        $connection = new PDO($dsn, $username, $password, $options);
        $sql = "SELECT plants.id AS plant_id, plants.species, soil.id AS soil_id, soil.soil_type 
				FROM plants, soil, plants_soil
				WHERE plants_soil.plant_id = plants.id
				AND plants_soil.soil_id = soil.id";
 
        $statement = $connection->prepare($sql);
        $statement->execute();
        $result = $statement->fetchAll();
?>

<!--Table Section-->
<br/>
<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			<h2>Display the plants_soil table.</h2>
		<hr>

		<form method = "post">
		<input name="csrf" type="hidden" value="<?php echo escape($_SESSION['csrf']); ?>">
		<table style = "width:100%">
			<tr>
				<th>Plant ID</th>
				<th>Plant Species</th>
				<th>Soil ID</th>
				<th>Soil Type</th>
				<th>Delete</th>
			</tr>

			<?php foreach ($result as $row) { ?>
            <tr>
                <td><?php echo escape($row["plant_id"]); ?></td>
                <td><?php echo escape($row["species"]); ?></td>
                <td><?php echo escape($row["soil_id"]); ?></td>
                <td><?php echo escape($row["soil_type"]); ?></td>
                <td>
					<button type="submit" name="deletePlantsSoil" class="btn" value="<?php echo escape($row["plant_id"]); ?>">DELETE</button>
				</td>
            </tr>
        	<?php } ?>

		</table>
		</form>

	</div>
</div>
</div>

<!-- Delete a row from table -->
<?php

$success = null;
if (isset($_POST["deletePlantsWatering"])) {
  
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
  
    $id = $_POST["deletePlantsWatering"];
    $sql = "DELETE FROM plants_watering WHERE plant_id = :plant_id";
    $statement = $connection->prepare($sql);
    $statement->bindValue(':plant_id', $id);
    $statement->execute();
    $success = "Link successfully deleted";
  } catch(PDOException $error) {
    echo $sql . "<br>" . $error->getMessage();
  }
}

?>




<br/>
<br/>
<br/>
<br/>


<!--Add New Watering Connection Form-->
<div class = "container-fluid form-group contactForm">
<form id = "waterForm" name = "waterConnection" method = "post" role="form" class="form-horizontal" >
    <fieldset>
        <legend>Create A New Plant and Watering Connection</legend>
        <hr>
            
        <label>Plant Species
        	<br/>
        	<?php 
           		$connection = new PDO($dsn, $username, $password, $options);
        		$sql = "SELECT id AS plant_id, species FROM plants";
        		$statement = $connection->prepare($sql);
				$statement->execute();
				$species = $statement->fetchAll();
			?>
            <select name = "plant_id" id = "plant_id">
            	<?php foreach($species as $plant): ?>
        		<option value="<?= $plant['plant_id']; ?>"><?= $plant['plant_id']; ?>. <?= $plant['species']; ?></option>
    			<?php endforeach; ?>
            </select>
       	</label>

      	<label>Watering Days
        	<br/>
            <?php 
           		$connection = new PDO($dsn, $username, $password, $options);
        		$sql = "SELECT id AS watering_id, days FROM watering_cycle";
        		$statement = $connection->prepare($sql);
				$statement->execute();
				$waters = $statement->fetchAll();
			?>
			<select name = "watering_id" id = "watering_id">
            	<?php foreach($waters as $water): ?>
        		<option value="<?= $water['watering_id']; ?>"><?= $water['watering_id']; ?>. <?= $water['days']; ?> days</option>
    			<?php endforeach; ?>
            </select>
       	</label>

       
        <input type = "submit" name = "submitWaterConnection" value = "Submit" />
            
    </fieldset>
</form>

<?php
if (isset($_POST['submitWaterConnection'])) 
{
    
    try  {
        $connection = new PDO($dsn, $username, $password, $options);
        
        $new_connection = array(
            "plant_id" 			=> $_POST['plant_id'],
            "watering_id"  		=> $_POST['watering_id']
        );

        $sql = sprintf(
                "INSERT INTO %s (%s) values (%s)",
                "plants_watering",
                implode(", ", array_keys($new_connection)),
                ":" . implode(", :", array_keys($new_connection))
        );
        
        $statement = $connection->prepare($sql);
        $statement->execute($new_connection);
    } 

    catch(PDOException $error)
    {
        echo $sql . "<br>" . $error->getMessage();
    }
}
?>

<br/>
<hr>
</div>

<!-- Select and dipslay plants_watering table -->
<?php
 		$connection = new PDO($dsn, $username, $password, $options);
        $sql = "SELECT plants.id AS plant_id, plants.species, watering_cycle.id AS watering_id, watering_cycle.days 
				FROM plants, watering_cycle, plants_watering
				WHERE plants_watering.plant_id = plants.id
				AND plants_watering.watering_id = watering_cycle.id";
 
        $statement = $connection->prepare($sql);
        $statement->execute();
        $result = $statement->fetchAll();
?>
<!--Table Section-->
<br/>
<div class = "container-fluid padding">
	<div class = "row welcomeSection text-center">
		<div class = "col-12">
			<h2>Display the plants_watering table.</h2>
		<hr>
		<form method = "post">
		<input name="csrf" type="hidden" value="<?php echo escape($_SESSION['csrf']); ?>">
		<table style = "width:100%">
			<tr>
				<th>Plant ID</th>
				<th>Plant Species</th>
				<th>Watering ID</th>
				<th>Days</th>
				<th>Delete</th>
			</tr>

			<?php foreach ($result as $row) { ?>
            <tr>
                <td><?php echo escape($row["plant_id"]); ?></td>
                <td><?php echo escape($row["species"]); ?></td>
                <td><?php echo escape($row["watering_id"]); ?></td>
                <td><?php echo escape($row["days"]); ?></td>
                <td>
					<button type="submit" name="deletePlantsWatering" class="btn" value="<?php echo escape($row["plant_id"]); ?>">DELETE</button>
				</td>
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