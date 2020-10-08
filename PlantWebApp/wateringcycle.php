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
				<li class = "nav-item active">
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
			<h1 class = "display-4">Watering Cycle</h1>
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
 * Use an HTML form to create a new entry in the table.
 ***********************************************/
if (isset($_POST['submit'])) 
{

    try  {
        $connection = new PDO($dsn, $username, $password, $options);
        
        $new_watering_cycle = array(
            "days" 		=> $_POST['days']
        );

        $sql = sprintf(
                "INSERT INTO %s (%s) values (%s)",
                "watering_cycle",
                implode(", ", array_keys($new_watering_cycle)),
                ":" . implode(", :", array_keys($new_watering_cycle))
        );
        
        $statement = $connection->prepare($sql);
        $statement->execute($new_watering_cycle);
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
        $sql = "SELECT * FROM watering_cycle";
 
        $statement = $connection->prepare($sql);
        $statement->execute();
        $result = $statement->fetchAll();
?>


<!--Add New Water Form-->
<div class = "container-fluid form-group contactForm">
<form id = "waterForm" name = "newWater" method = "post" role="form" class="form-horizontal" >
    <fieldset>
        <legend>Enter a new watering cycle.</legend>
        <hr>
            
        <label>Days
        	<br/>
            <input type = "number" class = "submissionField" name = "days" id = "days" min = "0" max = "364" size = "20" maxlength = "50" placeholder = "Required Integer" required>
       	</label>

        <input type = "submit" name = "submit" value = "Submit" />
            
    </fieldset>
</form>

<br/>

<br/>

</div>
<br/>
<hr>


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
    $sql = "DELETE FROM watering_cycle WHERE id = :id";
    $statement = $connection->prepare($sql);
    $statement->bindValue(':id', $id);
    $statement->execute();
    $success = "Watering Cycle successfully deleted";
  } catch(PDOException $error) {
    echo $sql . "<br>" . $error->getMessage();
  }
}
try {
  $connection = new PDO($dsn, $username, $password, $options);
  $sql = "SELECT * FROM watering_cycle";
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
			<h1 class = "display-4">Display the watering cycle table.</h1>
		<hr>

		<form method = "post">
		<input name="csrf" type="hidden" value="<?php echo escape($_SESSION['csrf']); ?>">
		<table style = "width:100%">
			<tr>
				<th>ID</th>
				<th>Days</th>
				<th>Update</th>
				<th>Delete</th>
			</tr>

			<?php foreach ($result as $row) { ?>
            <tr>
                <td><?php echo escape($row["id"]); ?></td>
                <td><?php echo escape($row["days"]); ?></td>
                <td><a href="updatewateringcycle.php?id=<?php echo escape($row["id"]); ?>">UPDATE</a></td>
				<td>
					<button type="submit" name="delete" class="btn" value="<?php echo escape($row["id"]); ?>">DELETE</button>
				</td>
            </tr>
        	<?php } ?>


		</table>
		</form>
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