__FILE__ =~ /([\w.\/-]+)\.t/;
exec($1) or die("exec $1");
