
<?php
//index.php

$error = '';
$name = '';
$email = '';
$gender = '';
$logo = '';
$feedback = '';

function clean_text($string)
{
 $string = trim($string);
 $string = stripslashes($string);
 $string = htmlspecialchars($string);
 return $string;
}

if(isset($_POST["submit"]))
{
 if(empty($_POST["name"]))
 {
  $error .= '<p><label class="text-danger">Please Enter your Name</label></p>';
 }
 else
 {
  $name = clean_text($_POST["name"]);
  if(!preg_match("/^[a-zA-Z ]*$/",$name))
  {
   $error .= '<p><label class="text-danger">Only letters and white space allowed</label></p>';
  }
 }
 if(empty($_POST["email"]))
 {
  $error .= '<p><label class="text-danger">Please Enter your Email</label></p>';
 }
 else
 {
  $email = clean_text($_POST["email"]);
  if(!filter_var($email, FILTER_VALIDATE_EMAIL))
  {
   $error .= '<p><label class="text-danger">Invalid email format</label></p>';
  }
 }
 if(empty($_POST["gender"]))
 {
  $error .= '<p><label class="text-danger">Gender is required</label></p>';
 }
 else
 {
  $gender = clean_text($_POST["gender"]);
 }
 if(empty($_POST["logo"]))
 {
  $error .= '<p><label class="text-danger">Logo should be selected</label></p>';
 }
 else
 {
  $logo = clean_text($_POST["logo"]);
 }
 if(empty($_POST["feedback"]))
 {
  $error .= '<p><label class="text-danger">Feedback is required</label></p>';
 }
 else{
  $feedback = clean_text($_POST["feedback"]);
 }
 if($error == '')
 {
  $file_open = fopen("contact_data.csv", "a");
  $no_rows = count(file("contact_data.csv"));
  if($no_rows > 1)
  {
   $no_rows = ($no_rows - 1) + 1;
  }
  $form_data = array(
   'sr_no'  => $no_rows,
   'name'  => $name,
   'email'  => $email,
   'gender' => $gender,
   'logo' => $logo,
   'feedback' => $feedback
  );
  fputcsv($file_open, $form_data);
  $error = '<label class="text-success">Thank you for filling the form</label>';
  $name = '';
  $email = '';
  $gender = '';
  $logo = '';
  $feedback = '';
 }
}

?>
<!DOCTYPE html>
<html>
 <head>
  <title>Satyanweshi Chatbot Evaluation</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
 </head>
 <body>
  <br />
  <div class="container">
   <h2 align="center">Satyanweshi Chatbot Evaluation</h2>
   <br />
   <div class="col-md-6" style="margin:0 auto; float:none;">
    <form method="post">
     <h3 align="center">Annotator's Evaluation Form</h3>
     <br />
     <?php echo $error; ?>
     <div class="form-group">
      <label>Enter Name</label>
      <input type="text" name="name" placeholder="Enter Name" class="form-control" value="<?php echo $name; ?>" />
     </div>
     <div class="form-group">
      <label>Enter Email</label>
      <input type="text" name="email" class="form-control" placeholder="Enter Email" value="<?php echo $email; ?>" />
     </div>
     <div class="form-group">
      <label>Select Gender</label><br>
      <input type="radio" id="male" name="gender" placeholder="Select Gender" value="male">
      <label for="male">Male</label>
      <input type="radio" id="female" name="gender" placeholder="Select Gender" value="female">
      <label for="female">Female</label>
     </div>
     <div class="form-group">
      <label>Select one of the logos</label><br>
      <img align="left" src="logo1.png" alt="Satyanweshi Logo 1" style="width:250px;height:250px;">
      <img align="right" src="logo2.png" alt="Satyanweshi Logo 2" style="width:250px;height:250px;"><br>
      &emsp; &emsp; &emsp; &emsp; &emsp;
      <label for="logo1">Logo 1</label>
      <input type="radio" id="logo1" name="logo" placeholder="Select Logo" value="logo1"> &emsp; &emsp; &emsp;&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp;
      <label for="logo2">Logo 2</label>
      <input type="radio" id="logo2" name="logo" placeholder="Select Logo" value="logo2"><br>
     </div>
     <div class="form-group">
      <label>Any other feedback</label>
      <textarea name="feedback" class="form-control" placeholder="Enter Feedback"><?php echo $feedback; ?></textarea>
     </div>
     <div class="form-group" align="center">
      <input type="submit" name="submit" class="btn btn-info" value="Submit" />
     </div>
    </form>
   </div>
  </div>
 </body>
</html>
