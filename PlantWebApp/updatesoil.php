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
					<a class = "nav-link active" href="soil.php">SOIL</a>
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
			<h1 class = "display-4">Update Soil Information</h1>
		</div>
		<hr>
	</div>
</div>



<?php

require "config.php";
require "common.php";
?>

<?php
if (isset($_POST['submit'])) {

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
    $soil = array(
      "id"          => $_POST['id'],
      "soil_type" 	=> $_POST['soil_type'],
      "soil_ph"  	  => $_POST['soil_ph'],
      "fertilizer"  => $_POST['fertilizer']

    );

    $sql = "UPDATE soil
            SET id = :id, 
              soil_type = :soil_type, 
              soil_ph = :soil_ph, 
              fertilizer = :fertilizer

            WHERE id = :id";
  
  $statement = $connection->prepare($sql);
  $statement->execute($soil);
  } catch(PDOException $error) {
      echo $sql . "<br>" . $error->getMessage();
  }

}
  
if (isset($_GET['id'])) {
  try {
    $connection = new PDO($dsn, $username, $password, $options);
    $id = $_GET['id'];
    $sql = "SELECT * FROM soil WHERE id = :id";
    $statement = $connection->prepare($sql);
    $statement->bindValue(':id', $id);
    $statement->execute();
    
    $soil = $statement->fetch(PDO::FETCH_ASSOC);
  } catch(PDOException $error) {
      echo $sql . "<br>" . $error->getMessage();
  }
} else {
    echo "Something went wrong!";
    exit;
}
?>





<div class = "container-fluid form-group contactForm">
<form method = "post" role="form" class="form-horizontal" >
    <fieldset>
        
        <hr>
            
        <label>ID
          <br/>
            <input type = "text" class = "submissionField" name = "id"  id = "id" size = "20" maxlength = "50" 
            value = "<?php echo escape(current($soil)); ?>" readonly>
        </label>

        <label>Soil Type
          <br/>
            <input type = "text" class = "submissionField" name = "soil_type" id = "soil_type" size = "20" maxlength = "50" value = "<?php echo escape(next($soil)); ?>" required>
        </label>

        <label id = "soilph">Soil pH
          <br/>
            <input type = "number" class = "submissionField" name = "soil_ph" id = "soil_ph" min = "1" max = "14" size = "20" maxlength = "50" value = "<?php echo escape(next($soil)); ?>" required>
        </label>

        <label>Fertilizer
          <br/>
            <input type = "number" class = "submissionField" name = "fertilizer" id = "fertilizer" min = "0" max = "1" size = "20" maxlength = "50" value = "<?php echo escape(next($soil)); ?>" required>
        </label>


        <input type = "submit" name = "submit" value = "Submit" />
            
    </fieldset>
</form>
</div>



<?php if (isset($_POST['submit']) && $statement) : ?>
	<br/>
	<p>Update Successful!</p>
	<a href="soil.php">CLICK HERE TO GO SEE THE UPDATED SOIL TABLE</a>
<?php endif; ?>


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