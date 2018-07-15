module Subscription = {
  type t;
  [@bs.send] external unsubscribe : t => unit = "";
};

module SubscriptionObserver = {
  type t('a);
  [@bs.send] external next : (t('a), 'a) => unit = "";
  [@bs.send] external error : (t('a), 'a) => unit = "";
  [@bs.send] external complete : unit => unit = "";
};

