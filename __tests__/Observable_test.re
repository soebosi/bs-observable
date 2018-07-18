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
  testAsync("map", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.map(string_of_int)
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe("10") |> finish
       )
    |. ignore
  );
  testAsync("filter", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.next(20);
      observer |. SubscriptionObserver.next(30);
      ignore;
    })
    |. Observable.filter(a =>
         if (a == 20) {
           true;
         } else {
           false;
         }
       )
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe(20) |> finish
       )
    |. ignore
  );
  testAsync("reduce", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.next(20);
      observer |. SubscriptionObserver.next(30);
      observer |. SubscriptionObserver.complete();
      ignore;
    })
    |. Observable.reduce((acc, value) => acc ++ string_of_int(value), "00")
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe("00102030") |> finish
       )
    |. ignore
  );
  testAsync("concat", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.complete();
      ignore;
    })
    |. Observable.concat([|
         Observable.make((observer: SubscriptionObserver.t(int)) => {
           observer |. SubscriptionObserver.next(20);
           observer |. SubscriptionObserver.complete();
           ignore;
         }),
         Observable.make((observer: SubscriptionObserver.t(int)) => {
           observer |. SubscriptionObserver.next(30);
           observer |. SubscriptionObserver.complete();
           ignore;
         }),
       |])
    |. Observable.reduce((acc, value) => [value, ...acc], [])
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual([30, 20, 10]) |> finish
       )
    |. ignore
  );
});
