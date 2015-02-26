<table class="table table-striped">
    <thead>
        <tr>
            <th>Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Action</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($positions as $position): ?>
        <tr>
            <td><?= $position["time"] ?></td>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= $position["price"] ?></td>
            <td><?= $position["action"] ?></td>
        </tr>
        <?php endforeach ?>
    </tbody>
</table>
