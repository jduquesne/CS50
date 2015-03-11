<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {        
        // validate submission
        if (empty($_POST["password"])) {
            apologize("Please provide your new password.");
        }
        else if ($_POST["confirmation"] != $_POST["password"]) {
            apologize("Please confirm your new password.");
        }

        // update user's password in database
        $id = $_SESSION["id"];
        query("UPDATE users SET hash = ? WHERE id = $id", crypt($_POST["password"]));
           
        // redirect to password page
        render("password.php", ["title" => "Password reset"]);
    }
    else
    {
        // else render form
        render("password_form.php", ["title" => "Password reset"]);
    }
?>
