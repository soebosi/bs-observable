module Subscription = {
  type t;
  [@bs.send] external unsubscribe : t => unit = "";
};
