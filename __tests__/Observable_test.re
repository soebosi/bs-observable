open Jest;

describe("Observable", () => {
  testAsync("subscribe", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe(10) |> finish
       )
    |. ignore
  );
  testAsync("forEach", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.forEach((x, _) =>
         Expect.expect(x) |> Expect.toBe(10) |> finish
       )
    |> Js.Promise.then_(() => Js.Promise.resolve())
    |. ignore
  );
});
