<p>Your available cash is: $<?= number_format($cash,2,".",",") ?></p>
<p>What do you want to buy ?</p>

<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="Ticker symbol" type="text"/>
        </div>      
        <div class="form-group">
            <input autofocus class="form-control" name="shares" placeholder="No. of shares" type="text"/>
        </div>      
        <div class="form-group">
            <button type="submit" class="btn btn-default">Buy stock</button>
        </div>
    </fieldset>
</form>
