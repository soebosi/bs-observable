class subject ('a) = {
  val observer = ref(None);
  val stream = ref(None);
  pub make = () => {
    stream :=
      Observable.make((o: SubscriptionObserver.t('a)) => {
        observer := Some(o);
        () => {
          observer := None;
          stream := None;
        };
      })
      |. Some;
    this;
  };
  pub next = v => {
    Belt.Option.map(observer^, o => o |. SubscriptionObserver.next(v))
    |. ignore;
    this;
  };
  pub complete = () =>
    Belt.Option.map(observer^, o => o |. SubscriptionObserver.complete())
    |. ignore;
  pub stream = () => Belt.Option.getExn(stream^);
};

type t('a) = subject('a);

let make = () : t('a) => {
  let s: t('a) = new subject;
  s#make();
};

let next = (s: t('a), v: 'a) => s#next(v);

let complete = (s: t('a)) => s#complete();

let asStream = (s: t('a)) => s#stream();
