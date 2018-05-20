open Reprocessing;

type stateT = {
  image: imageT,
};

let setup = (env) => {
  Env.size(~width=800, ~height=600, env);
  let image = Draw.loadImage(
    ~filename="assets/Wave_pattern_by_inkelv1122_on_flickr_800w.jpg", 
    ~isPixel=false, env);
  {
    image: image
  }
};

let draw = ({image} as state, env) => {
  Draw.background(Constants.white, env);
  Draw.image(
    image,
    ~pos=(0,0),
    ~width=Env.width(env),
    ~height=Env.height(env),
    env
  );
  state
};

run(~setup, ~draw, ());
