<?php
// データベースの作成と接続(既にある場合は接続のみ)
$db = new PDO('sqlite:ranking.db');

// ランキング上位10件を取得するクエリ
$que = "SELECT * FROM Ranking ORDER BY clearTime LIMIT 10";
$value = $db->query($que)->fetchAll(PDO::FETCH_ASSOC);

// JSON形式で結果を返す
echo json_encode($value);
?>