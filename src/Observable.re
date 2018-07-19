type t('a);
[@bs.new] [@bs.module]
external make : ((SubscriptionObserver.t('a), unit) => unit) => t('a) =
  "zen-observable";

[@bs.send] external subscribe : (t('a), 'a => unit) => Subscription.t = "";

[@bs.send]
external forEach : (t('a), ('a, unit => unit) => unit) => Js.Promise.t(unit) =
  "";

[@bs.send] external map : (t('a), 'a => 'b) => t('b) = "";

[@bs.send] external filter : (t('a), 'a => bool) => t('a) = "";

[@bs.send] external reduce : (t('a), ('b, 'a) => 'b, 'b) => t('b) = "";

[@bs.send] [@bs.splice]
external concat : (t('a), array(t('a))) => t('a) = "";

[@bs.send] external flatMap : (t('a), 'a => array('a)) => t('a) = "";

[@bs.module "zen-observable"] [@bs.splice]
external of_ : array('a) => t('a) = "of";
