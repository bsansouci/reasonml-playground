open Reprocessing;

type runningT =
  | Running
  | Dead
  | Restart;

type stateT = {
  running: runningT,
  image: imageT,
};

type pieceT = {
  key: string,
  row: int,
  col: int,
  cellSize: int,
};

let getPuzzlePieceId = (row: int, col: int, cellSize: int): string => {
  let rowStr = string_of_int(row);
  let colStr = string_of_int(col);
  let cellSizeStr = string_of_int(cellSize);
  "w" ++ cellSizeStr ++ "_r" ++ rowStr ++ "_c" ++ colStr;
};

let getPiece = (numColumns: int, cellSize: int, i: int): pieceT => {
  let row = i / numColumns;
  let col = i mod numColumns;
  let key = getPuzzlePieceId(row, col, cellSize);
  { key, row, col, cellSize };
};

let getPiecesArray = (numRows, numColumns, cellSize): array(pieceT) => {
  Array.init(numRows * numColumns, i => getPiece(numColumns, cellSize, i))
};

let setup = (env) => {
  Env.size(~width=800, ~height=600, env);
  let image = Draw.loadImage(
    ~filename="assets/Wave_pattern_by_inkelv1122_on_flickr_800w.jpg", 
    ~isPixel=false, env);
  let imgWidth = switch image.glData {
  | Some(_glData) => _glData.width
  | _ => 0
  };
  let imgHeight = switch image.glData {
  | Some(_glData) => _glData.height
  | _ => 0
  };
  print_endline(string_of_int(imgWidth));
  print_endline(string_of_int(imgHeight));
  {
    running: Running,
    image,
  }
};

let draw = ({image} as state, env) => {
  Draw.background(Constants.white, env);
  Draw.image(
    image,
    ~pos=(0,0),
    /* ~width=Env.width(env), */
    /* ~width=800,
    ~height=600, */
    env
  );
  state
};

run(~setup, ~draw, ());
