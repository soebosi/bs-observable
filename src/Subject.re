class subject ('a) = {
  as _self;
  val mutable observer: option(SubscriptionObserver.t('a)) = None;
  pub make = () : Observable.t('a) =>
    Observable.make((o: SubscriptionObserver.t('a)) => {
      o |. SubscriptionObserver.next(10);
      observer = Some(o);
      ignore;
    });
  pub next = v =>
    Belt.Option.getExn(observer) |. SubscriptionObserver.next(v);
};

type t('a) = subject('a);

let make = () : t('a) => {
  let s: t('a) = new subject;
  s#make();
  s;
};

let next = (s: subject('a), v: 'a) => s#next(v);
