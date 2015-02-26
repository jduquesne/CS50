<p>Your available cash is: $<?= number_format($cash,2,".",",") ?></p>
<p>Which position do you wish to sell ?</p>

<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="Ticker symbol" type="text"/>
        </div>      
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell stock</button>
        </div>
    </fieldset>
</form>
