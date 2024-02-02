set schema 'shopify';

begin transaction;

update shopify.pricing_plans set price = 10 where price = 0 and title = 'Startup';
update shopify.pricing_plans set title = 'New_Startup_Price' where price = 10 and title = 'Startup';

commit;
