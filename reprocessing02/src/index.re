open Reprocessing;

 type runningT =
   | Running
   | Dead
   | Restart;

 type pieceT = {
   key: string,
   row: int,
   col: int,
   cellSize: int,
 };

 type loadedImageT = {
   image: imageT,
   width: int,
   height: int,
 };

 type imageTileT = {
   piece: pieceT,
   image: loadedImageT,
 }; 

 type stateT = {
   running: runningT,
     pieces: array(imageTileT),
     image: imageT,
};

let getPuzzlePieceId = (row: int, col: int, cellSize: int) : string => {
  let rowStr = string_of_int(row);
  let colStr = string_of_int(col);
  let cellSizeStr = string_of_int(cellSize);
  "w" ++ cellSizeStr ++ "_r" ++ rowStr ++ "_c" ++ colStr;
};

let getPiece = (numColumns: int, cellSize: int, i: int) : pieceT => {
  let row = i / numColumns;
  let col = i mod numColumns;
  let key = getPuzzlePieceId(row, col, cellSize);
  {key, row, col, cellSize};
};

let getPiecesArray = (numRows, numColumns, cellSize) : array(pieceT) =>
  Array.init(numRows * numColumns, i => getPiece(numColumns, cellSize, i));

let setup = env => {
  Env.size(~width=800, ~height=600, env);
  let image =
    Draw.loadImage(
      ~filename="assets/Wave_pattern_by_inkelv1122_on_flickr_800w.jpg",
      ~isPixel=false,
      env,
    );
    let imgWidth =
    switch (image.glData) {
    | Some(_glData) => _glData.width
    | _ => 0
    };
  let imgHeight =
    switch (image.glData) {
    | Some(_glData) => _glData.height
    | _ => 0
    };
  print_endline(string_of_int(imgWidth));
  print_endline(string_of_int(imgHeight));
  let getImgTile = (piece: pieceT) : imageTileT => {
    let tileData: loadedImageT = {image, width: imgWidth, height: imgHeight};
    {piece, image: tileData};
  };
  let imageTiles: array(imageTileT) =
    getPiecesArray(60, 80, 10) |> Array.map(getImgTile);
  {running: Running, pieces: imageTiles, image}; 
};

drawImgTile = (tile: imageTileT, env) => {
  let {piece: (pieceData: pieceT), image: (loadedImage: loadedImageT)} = tile;
  let {image: (imageData: imageT), width, height}: loadedImageT = loadedImage;
  let {row, col, cellSize, key: _}: pieceT = pieceData;
  let pos = (col * cellSize, row * cellSize);
  Draw.subImage(
       imageData,
       ~pos: pos,
       ~width: cellSize,
       ~height: cellSize,
       ~texPos: (width / col, height / row),
       ~texWidth: width / cellSize,
       ~texHeight: height / cellSize,
       env
     ) 
};

let draw = ({image} as state, env) => {
  Draw.background(Constants.white, env);
  pieces |> Array.iter(imgTile => drawImgTile(imgTile, env));
  state;
};

run(~setup, ~draw, ());