<?php

    // configuration
    require("../includes/config.php"); 

    // set "id"
    $id = $_SESSION["id"];

    // process SQL query for portfolio
    $rows = query("SELECT * FROM history WHERE userid = $id");

    // set variables "positions"
    $positions = [];

    foreach ($rows as $row)
    {
        // iterate over symbol to extract stock info from Yahoo
        $positions[] = [
            "time" => $row["time"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"],
            "action" => $row["action"],
        ];
    }

    // redirect to history form
    render("history.php", ["positions" => $positions, "title" => "History"]);   

?>
