type t('a);
[@bs.send] external next : (t('a), 'a) => unit = "";
[@bs.send] external error : (t('a), 'a) => unit = "";
[@bs.send] external complete : unit => unit = "";
