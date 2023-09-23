#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
const int N=1e5+5;
struct node
{
	int l,r;
	tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> idx;
};
struct infor{int val,idx;};
struct askinfor{int l,r,k;};
int n,m,l,r,k,tot,tab[N<<1];
char init;
node tr[N<<3];
infor a[N];
askinfor pushq,query[N];
set<int> appe;
unordered_map<int,int> extab;
inline bool cmp(infor p,infor q){return p.val<q.val;}
inline bool cmp2(infor p,infor q){return p.idx<q.idx;}
const int BUFSIZE = 1 << 20;
char ibuf[BUFSIZE], *is = ibuf, *it = ibuf;
inline char getch(){
	if(is == it)
		it = (is = ibuf) + fread(ibuf, 1, BUFSIZE, stdin);
	return is == it ? EOF : *is++;
}
inline int read(){
	int res = 0, neg = 0, ch = getch();
	while(!(isdigit(ch) or ch == '-') and ch != EOF)
		ch = getch();
	if(ch == '-')
		neg = 1, ch = getch();
	while(isdigit(ch))
		res = (res<<3)+(res<<1) + (ch - '0'), ch = getch();
	return neg ? -res : res;
}
inline int find(int l,int r,int k)
{
	int mid;
	while(l<r) mid=(l+r)+1>>1,(a[mid].val<=k)?l=mid:r=mid-1;
	return l;
}
inline void build(int p,int l,int r,int al,int ar)
{
	tr[p].l=l,tr[p].r=r;
	for(int i(al);i<=ar;++i) tr[p].idx.insert(a[i].idx);
	if(l==r) return;
	int mid((l+r)>>1),mididx(find(al,ar,mid));
	if(a[al].val>mid) mididx=al-1;
	build(p<<1,l,mid,al,mididx),build(p<<1|1,mid+1,r,mididx+1,ar);
	return;
}
inline void del(int p,int idx)
{
	tr[p].idx.erase(idx);
	if(tr[p].l==tr[p].r) return;
	(a[idx].val<=tr[p].l+tr[p].r>>1)?del(p<<1,idx):del(p<<1|1,idx);
}
inline void add(int p,int idx)
{
	tr[p].idx.insert(idx);
	if(tr[p].l==tr[p].r) return;
	(a[idx].val<=tr[p].l+tr[p].r>>1)?add(p<<1,idx):add(p<<1|1,idx);
	return;
}
inline bool appear(int p,int k){return (*tr[p].idx.lower_bound(k))==k;}
inline int ask(int p,int l,int r,int k)
{
	if(tr[p].l==tr[p].r) return tr[p].l;
	int rkr,rkl;
	if(appear(p<<1,r)) rkr=tr[p<<1].idx.order_of_key(r)+1;
	else
	{
		tr[p<<1].idx.insert(r);
		rkr=tr[p<<1].idx.order_of_key(r);
		tr[p<<1].idx.erase(r);
	}
	if(appear(p<<1,l-1)) rkl=tr[p<<1].idx.order_of_key(l-1)+1;
	else
	{
		tr[p<<1].idx.insert(l-1);
		rkl=tr[p<<1].idx.order_of_key(l-1);
		tr[p<<1].idx.erase(l-1);
	}
	if(rkr-rkl>=k) return ask(p<<1,l,r,k);
	else return ask(p<<1|1,l,r,k-rkr+rkl);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	extab.reserve(N<<1);
	for(int i(1);i<=n;++i)	a[i].val=read(),appe.insert(a[i].val),a[i].idx=i;
	sort(a+1,a+n+1,cmp);
	for(int i(1);i<=m;++i)
	{
		cin>>init;
		if(init=='Q') query[i].l=read(),query[i].r=read(),query[i].k=read();
		else
		{
			query[i].l=read(),query[i].r=read(),query[i].k=-1;
			appe.insert(query[i].r);
		}
	}
	for(auto it=appe.begin();it!=appe.end();++it) tab[++tot]=(*it),extab[(*it)]=tot;
	for(int i(1);i<=n;++i) a[i].val=extab[a[i].val];
	build(1,1,tot,1,n);
	sort(a+1,a+n+1,cmp2);
	for(int i(1);i<=m;++i)
	{
		if(query[i].k==-1) del(1,query[i].l),a[query[i].l].val=extab[query[i].r],add(1,query[i].l);
		else cout << tab[ask(1,query[i].l,query[i].r,query[i].k)] << '\n';
	}
	return 0;
}
