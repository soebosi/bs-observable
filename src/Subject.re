class subject ('a) = {
  val mutable observer: option(SubscriptionObserver.t('a)) = None;
  pub make = () => {
    Observable.make((o: SubscriptionObserver.t('a)) => {
      observer = Some(o);
      ignore;
    })
    |. ignore;
    this;
  };
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
