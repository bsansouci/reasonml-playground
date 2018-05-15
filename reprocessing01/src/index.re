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
  {
    running: Running,
    image: Draw.loadImage(~filename="assets/Wave_pattern_by_inkelv1122_on_flickr.jpg", ~isPixel=true, env),
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
  Draw.subImage(
    image,
    ~pos=(int_of_float(-. xOffset) mod width + width, int_of_float(y)),
    ~width,
    ~height,
    ~texPos,
    ~texWidth,
    ~texHeight,
    env
  )
};

let draw = ({image, running} as state, env) => {
  drawTiledThing(
    state,
    ~texPos=(0, 0),
    ~texWidth=144,
    ~texHeight=256,
    ~xOffset=xOffset /. 2.,
    ~y=0.,
    ~height=Env.height(env),
    env
  );

run(~setup, ~draw, ());
