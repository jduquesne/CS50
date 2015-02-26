<table class="table table-striped">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Last price</th>
            <th>Mkt value</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($positions as $position): ?>
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= number_format($position["price"],2,".",",") ?></td>
            <td>$<?= number_format(($position["shares"] * $position["price"]),2,".",",") ?></td>
        </tr>
        <?php endforeach ?>
        <tr>
            <td>CASH</td>
            <td>Cash available</td>
            <td></td>
            <td></td>
            <td>$<?= number_format($cash,2,".",",") ?></td>
        </tr>
    </tbody>
</table>
