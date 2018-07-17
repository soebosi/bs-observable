open Jest;

describe("Observable", () =>
  testAsync("subscribe", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe(10) |> finish
       )
    |. ignore
  )
);
