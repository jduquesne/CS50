<?php

    // configuration
    require("../includes/config.php"); 

    // if stock symbol was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {           
        $stock = lookup($_POST["symbol"]); 

        // validate submission
        if ($stock == false)
        {
            apologize("You must provide a valid stock symbol.");
        }
                
        // redirect to quote page dispalying stock info
        render("quote.php");
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "quote form"]);
    }

?>


