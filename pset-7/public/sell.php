<?php

    // configuration
    require("../includes/config.php"); 

    // set variable "id"
    $id = $_SESSION["id"];
    
    // process SQL queries to get arrays
    $rows = query("SELECT * FROM portfolio WHERE id = $id");
    $cash = query("SELECT cash FROM users WHERE id = $id");
    
    // set variable "cash" and "position"
    $cash = $cash[0]["cash"];
    
    // if stock symbol was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {     
        $stock = lookup($_POST["symbol"]);      
        
        foreach ($rows as $row)
        {
            $position = $row["symbol"];
            
            // validate submission
            if ($stock["symbol"] == $position)
            {
                // redirect to sell page confirming sale        
                query("DELETE FROM portfolio WHERE id = $id AND symbol = '$position'");
                
                // update cash value
                $cash = $cash + $row["shares"] * $stock["price"]; 
                query("UPDATE users SET cash = '$cash' WHERE id = $id");

                // update history
                $symbol = strtoupper ($stock["symbol"]);
                $shares = $row["shares"];
                query("INSERT INTO history (userid, time, symbol, shares, price, action) VALUES(?, now(), ?, ?, ?, ?)", $id, $symbol, $shares, $stock["price"], "SELL");

                render("sell.php", ["cash" => $cash, "position" => $position, "title" => "Sold position"]);
                return true;
            }
        }
        apologize("Sorry, you can only sell stock you own.");
    }
    else
    {
        // render sell form
        render("sell_form.php", ["cash" => $cash, "title" => "Sell position"]);
    }    
?>


