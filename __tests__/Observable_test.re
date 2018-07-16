open Jest;

describe("Observable", () =>
  Expect.(
    testAsync("subscribe", finish =>
      Observable.make((observer: SubscriptionObserver.t(int)) => {
        observer |. SubscriptionObserver.next(10);
        ignore;
      })
      |. Observable.subscribe(x => finish(expect(x) |> toBe(10)))
      |. ignore
    )
  )
);
