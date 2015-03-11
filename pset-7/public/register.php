<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"])) {
            apologize("Please provide your username.");
        }
        else if (empty($_POST["email"])) {
            apologize("Please provide your email address.");
        }
        else if (!preg_match("/([\w\-]+\@[\w\-]+\.[\w\-]+)/", $_POST["email"])) {
            apologize("Please provide a valid email address.");
        }
        else if (empty($_POST["password"])) {
            apologize("Please provide your password.");
        }
        else if ($_POST["confirmation"] != $_POST["password"]) {
            apologize("Please confirm your password.");
        }

        // create user in database
        $entry = query("INSERT INTO users (username, email, hash, cash) VALUES(?, ?, ?, 10000.00)", $_POST["username"], $_POST["email"], crypt($_POST["password"]));
            
            // check if entry succeeded
            if ($entry === false) {
                apologize("Sorry, this login is already used, please select a new one.");
            }
            else {
                
                // find out which ID was assigned to the newly registered user
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                
                // remember that user's now logged in by storing user's ID in session
                $_SESSION["id"] = $id;
                
                // redirect to portfolio
                redirect("/");
            }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
