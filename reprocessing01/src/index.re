open Reprocessing;

type runningT =
  | Running
  | Dead
  | Restart;

type stateT = {
  running: runningT,
  image: imageT,
};

let setup = (env) => {
  Env.size(~width=400, ~height=640, env);
  let image = Draw.loadImage(
    ~filename="assets/Wave_pattern_by_inkelv1122_on_flickr.jpg", 
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

let drawTiledThing = ({image}, ~texPos, ~texWidth, ~texHeight, ~xOffset, ~y, ~height, env) => {
  let width = Env.width(env);
  Draw.subImage(
    image,
    ~pos=(int_of_float(-. xOffset) mod width, int_of_float(y)),
    ~width,
    ~height,
    ~texPos,
    ~texWidth,
    ~texHeight,
    env
  );
};

let draw = ({image, running} as state, env) => {
  /*drawTiledThing(
    state,
    ~texPos=(0, 0),
    ~texWidth=800,
    ~texHeight=500,
    ~xOffset=0. /. 1.,
    ~y=0.,
    ~height=Env.height(env),
    env
  );*/
  Draw.background(Constants.white, env);
  Draw.subImage(
    image,
    ~pos=(100, 100),
    ~width=30,
    ~height=30,
    ~texPos=(0,0),
    ~texWidth=60,
    ~texHeight=60,
    env
  );
  state
  /* switch running {
    | Running => {
        ...state,
        image
      }
    | Dead => {
        ...state,
        image
      }
    | Restart =>
      if (Env.keyPressed(Space, env)) {
        {
          ...state,
          image
          running: Running,
        }
      } else {
        state
      }
  } */
};

run(~setup, ~draw, ());
