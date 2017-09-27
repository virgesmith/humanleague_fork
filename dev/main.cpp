
#include "src/IPF.h"
#include "src/QSIPF.h"
#include "src/Sobol.h"

// deprecated
#include "src/NDArrayUtilsOld.h"
#include "src/IndexOld.h"

// work-in-progress
#include "src/NDArray.h"
#include "src/Index.h"
#include "src/NDArrayUtils.h"

#include <map>

void do2d()
{
  std::vector<std::vector<int64_t>> m = {std::vector<int64_t>{52, 48}, 
                                        std::vector<int64_t>{10, 77, 13}};
                                    
  std::vector<int64_t> size{ (int64_t)m[0].size(), (int64_t)m[1].size() };                                        

  NDArray<double> s(size);
  s.assign(1.0);
  //Index index(s.sizes());
  //s[index] = 0.5;

  QSIPF qsipf(s, m);

  auto e = qsipf.errors();
  print(e[0]);
  print(e[1]);
  std::cout << qsipf.conv() << ":" << qsipf.iters() << ":" << qsipf.chiSq() << std::endl;
  print(qsipf.result().rawData(), qsipf.result().storageSize(), m[1].size());
  print(qsipf.sample().rawData(), qsipf.sample().storageSize(), qsipf.sample().sizes()[1]);
  print(reduce<int64_t>(qsipf.sample(), 0));
  print(reduce<int64_t>(qsipf.sample(), 1));
}

void do2dIPF()
{
  std::vector<std::vector<double>> m = {std::vector<double>{12, 40, 48}, 
                                        std::vector<double>{87, 13}};
                                    
  std::vector<int64_t> size{ (int64_t)m[0].size(), (int64_t)m[1].size() };                                        

  NDArray<double> s(size);
  s.assign(1.0);
  //Index index(s.sizes());
  //s[index] = 0.5;

  IPF ipf(s, m);

  auto e = ipf.errors();
  print(e[0]);
  print(e[1]);
  std::cout << ipf.conv() << ":" << ipf.iters() << std::endl;
  print(ipf.result().rawData(), ipf.result().storageSize(), m[1].size());
  print(reduce(ipf.result(), 0));
  print(reduce(ipf.result(), 1));
}


void do3d()
{
  std::vector<std::vector<int64_t>> m = {std::vector<int64_t>{52, 40, 4, 4}, 
                                        std::vector<int64_t>{87, 10, 3},
                                        std::vector<int64_t>{55, 15, 6,12, 12}};
  // std::vector<std::vector<double>> m = {std::vector<int64_t>{32, 32, 32, 32}, 
  //                                       std::vector<int64_t>{126, 1, 1},
  //                                       std::vector<int64_t>{64, 64}};

  std::vector<int64_t> size{ (int64_t)m[0].size(), (int64_t)m[1].size(), (int64_t)m[2].size() };                                        

  NDArray<double> s(size);
  s.assign(1.0);
  Index i(s.sizes());
  s[i] = 1.0;

  QSIPF qsipf(s, m);

  auto e = qsipf.errors();
  print(e[0]);
  print(e[1]);
  print(e[2]);
  // conv/iters/errors needs a rethink
  std::cout << qsipf.conv() << ":" << qsipf.iters() << ":" << qsipf.chiSq() << std::endl;
  //print(qsipf.result().rawData(), qsipf.result().storageSize(), m[1].size());

  //print(pop.rawData(), pop.storageSize(), pop.sizes()[1]);
  print(qsipf.sample().rawData(), qsipf.sample().storageSize(), qsipf.sample().sizes()[1]);
  print(reduce<int64_t>(qsipf.sample(), 0));
  print(reduce<int64_t>(qsipf.sample(), 1));
  print(reduce<int64_t>(qsipf.sample(), 2));
}

void do3dIPF()
{
  std::vector<std::vector<double>> m = {std::vector<double>{52, 48}, 
                                        std::vector<double>{10, 77, 13},
                                        std::vector<double>{20, 27, 30, 23}};
  
  std::vector<int64_t> size{ (int64_t)m[0].size(), (int64_t)m[1].size(), (int64_t)m[2].size() };                                        

  NDArray<double> s(size);
  s.assign(1.0);
  //Index index(s.sizes());
  //s[index] = 0.5;

  IPF ipf(s, m);

  auto e = ipf.errors();
  print(e[0]);
  print(e[1]);
  print(e[2]);
  std::cout << ipf.conv() << ":" << ipf.iters() << std::endl;
  print(ipf.result().rawData(), ipf.result().storageSize(), m[1].size());
  print(reduce(ipf.result(), 0));
  print(reduce(ipf.result(), 1));
  print(reduce(ipf.result(), 2));
}



void do4d()
{
  std::vector<std::vector<int64_t>> m = {std::vector<int64_t>{52, 48}, 
                                        std::vector<int64_t>{87, 13},
                                        std::vector<int64_t>{67, 33},
                                        std::vector<int64_t>{55, 45}};

  std::vector<int64_t> size{ (int64_t)m[0].size(), (int64_t)m[1].size(), (int64_t)m[2].size(), (int64_t)m[3].size() };                                        

  NDArray<double> s(size);
  s.assign(1.0);
  //Index index(s.sizes());
  //s[index] = 0.7;

  QSIPF qsipf(s, m);

  auto e = qsipf.errors();
  print(e[0]);
  print(e[1]);
  print(e[2]);
  print(e[3]);
  std::cout << qsipf.conv() << ":" << qsipf.iters() << ":" << qsipf.chiSq() << std::endl;
  print(qsipf.sample().rawData(), qsipf.sample().storageSize(), m[1].size());
  print(reduce<int64_t>(qsipf.sample(), 0));
  print(reduce<int64_t>(qsipf.sample(), 1));
  print(reduce<int64_t>(qsipf.sample(), 2));
  print(reduce<int64_t>(qsipf.sample(), 3));
}



template<typename T>
class MIPF
{
public:
  typedef std::vector<int64_t> index_t;
  typedef std::vector<index_t> index_list_t;
  typedef NDArray<T> marginal_t;
  typedef std::vector<marginal_t> marginal_list_t;

  typedef std::vector<std::pair<int64_t, int64_t>> marginal_indices_t;
  typedef std::vector<marginal_indices_t> marginal_indices_list_t;

  MIPF(const index_list_t& indices, marginal_list_t& marginals):
    m_indices(indices), m_marginals(marginals)
  {
    // i and m should be same size and >2
    if (m_indices.size() != m_marginals.size() || m_indices.size() < 2)
      throw std::runtime_error("index and marginal lists differ in size or too small");

    // count all unique values in i...
    std::map<int64_t, int64_t> dim_sizes;   
    for (size_t k = 0; k < m_indices.size(); ++k)
    {
      if (m_indices[k].size() != m_marginals[k].dim())
        throw std::runtime_error("index/marginal dimension mismatch " + std::to_string(m_indices[k].size()) + " vs " + std::to_string(m_marginals[k].dim()));
      //std::cout << "index " << k << std::endl;
      for (size_t j = 0; j < m_indices[k].size(); ++j)
      {
        int64_t dim = m_indices[k][j];
        int64_t size = m_marginals[k].size(j);
        // check if already entered that size is same
        auto posit = dim_sizes.find(dim);
        if (posit == dim_sizes.end())
          dim_sizes.insert(std::make_pair(dim, size));
        else if (posit->second != size)
          throw std::runtime_error("mismatch at index " + std::to_string(k) + 
            ": dimension " + std::to_string(dim) + " size " + std::to_string(posit->second) + " redefined to " + std::to_string(size));
        //std::cout << "  " << dim << ":" << size << std::endl;
      }
    }

    // check all dims defined
    std::vector<int64_t> sizes;
    sizes.reserve(m_indices.size());

    // we should expect that the dim_sizes map contains keys from 0 to dim_sizes.size()-1. if not throw
    for (size_t k = 0; k < dim_sizes.size(); ++k)
    {
      auto it = dim_sizes.find(k);
      if (it == dim_sizes.end())
        throw std::runtime_error("dimension " + std::to_string(k) + " size not defined");
      sizes.push_back(it->second);
    }


    // create mapping from dimension to marginal(s)
    m_dim = dim_sizes.size();
    m_dim_lookup.resize(m_dim);

    for (size_t k = 0; k < m_indices.size(); ++k)
      for (size_t i = 0; i < m_indices[k].size(); ++i)
        m_dim_lookup[m_indices[k][i]].push_back(std::make_pair(k,i));

    // check marginal sums all the same
    const size_t s = sum(m_marginals[0]);
    for (size_t i = 1; i < m_marginals.size(); ++i)
    {
      if (sum(m_marginals[i]) != s)
        throw std::runtime_error("marginal sum mismatch");
    }

    // check that for each dimension included in more than one marginal, the partial sums in that dimension are equal
    for (size_t d = 0; d < m_dim; ++d)
    {
      // loop over the relevant marginals
      const marginal_indices_t& mi = m_dim_lookup[d];
      if (mi.size() < 2)
        continue;
      //                                     marginal index            marginal dimension
      const std::vector<double>& ms = reduce(m_marginals[mi[0].first], mi[0].second);
      for (size_t i = 1; i < mi.size(); ++i)
      {
        if (reduce(m_marginals[mi[i].first], mi[i].second) != ms)
          throw std::runtime_error("marginal partial sum mismatch");
      }

    }

    m_array.resize(sizes);

    // print summary data
    std::cout << "Dim Size" << std::endl;
    for (size_t d = 0; d < sizes.size(); ++d)
    {  
      std::cout << d << ": " << sizes[d] << std::endl;
    }

    std::cout << "Mrg Dims" << std::endl;
    for (size_t k = 0; k < m_indices.size(); ++k)
    {
      std::cout << k << ": ";
      print(m_indices[k]);
    }

    std::cout << "Dim Mrg,Dim" << std::endl;
    for (size_t d = 0; d < m_dim_lookup.size(); ++d)
    {  
      std::cout << d << ":";
      for (size_t i = 0; i < m_dim_lookup[d].size(); ++i)
      {
        std::cout << m_dim_lookup[d][i].first << "," << m_dim_lookup[d][i].second << " ";
      }
      std::cout << std::endl;
    }
  }


  std::vector<MappedIndex> makeMappings(const Index& index_main)
  {
    std::vector<MappedIndex> mappings;
    mappings.reserve(m_marginals.size());
    for (size_t k = 0; k < m_marginals.size(); ++k)
    {
      mappings.push_back(MappedIndex(index_main, m_indices[k]));
    }
    return mappings;
  }

  bool computeErrors(std::vector<NDArray<double>>& diffs)
  {
    m_maxError = -std::numeric_limits<double>::max();

    // // create mapped indices
    // const std::vector<MappedIndex>& mapped = makeMappings(main_index);
    for (size_t k = 0; k < diffs.size(); ++k)
    {
      for (Index index(diffs[k].sizes()); !index.end(); ++index)
      {
        double e = std::fabs(diffs[k][index]);
        m_errors[k][index] = e;
        m_maxError = std::max(m_maxError, e);
      }
    }

    return m_maxError < m_tol;
  }  

  void rDiff(std::vector<NDArray<double>>& diffs, const NDArray<double>& result, const std::vector<NDArray<double>>& marginals)
  {
    int64_t n = m_indices.size();
    for (int64_t k = 0; k < n; ++k)
      diff(reduce<double>(result, m_indices[k]), marginals[k], diffs[k]);
  }

  // TODO move
  std::vector<int64_t> invert(size_t max, const std::vector<int64_t>& excluded)
  {
    std::cout << "invert " << max << std::endl; 
    print(excluded);
    std::vector<int64_t> included;
    included.reserve(max - excluded.size());
    for (size_t i = 0; i < max; ++i)
    {
      if (std::find(excluded.begin(), excluded.end(), i) == excluded.end())
        included.push_back(i);
    }
    print(included);
    return included;
  }

  
  void rScale()
  {
    // for (size_t d = 0; d < result.dim(); ++d)
    // {
    //   const std::vector<double>& r = reduce<double>(result, d);
    //   for (size_t p = 0; p < marginals[d].size(); ++p)
    //   {
    //     for (Index index(result.sizes(), { d, p }); !index.end(); ++index)
    //     {
    //       const std::vector<int64_t>& ref = index;
    //       // avoid division by zero (assume 0/0 -> 0)
    //       if (r[p] == 0.0 && marginals[d][ref[d]] != 0.0)
    //         throw std::runtime_error("div0 in rScale with m>0");
    //       if (r[p] != 0.0)
    //         result[index] *= marginals[d][ref[d]] / r[p];
    //       else
    //         result[index] = 0.0;
    //     }
    //   }
    // }
    for (size_t k = 0; k < m_indices.size(); ++k)
    {
      const NDArray<double>& r = reduce<double>(m_array, m_indices[k]);
      std::cout << k << ":";
      print(r.rawData(), r.storageSize());


      Index main_index(m_array.sizes());
      //std::cout << m_array.sizes()[m_indices[1-k][0]] << std::endl;
      for (MappedIndex oindex(main_index, invert(m_array.dim(), m_indices[k])); !oindex.end(); ++oindex)
      {
        for (MappedIndex index(main_index, m_indices[k]); !index.end(); ++index)
        {
          print((std::vector<int64_t>)main_index);
          if (r[index] == 0.0 && m_marginals[k][index] != 0.0)
            throw std::runtime_error("div0 in rScale with m>0");
          if (r[index] != 0.0)
            m_array[main_index] *= m_marginals[k][index] / r[index];
          else
            m_array[main_index] = 0.0;
        }
      }
      // reset the main index
      //main_index.reset();
    }
  }
  
  NDArray<double>& doP()
  {
    Index index_main(m_array.sizes());

    std::vector<MappedIndex> mappings = makeMappings(index_main);

    m_array.assign(1.0);
    for (; !index_main.end(); ++index_main)
    {
      for (size_t k = 0; k < m_marginals.size(); ++k)
      {
        m_array[index_main] *= m_marginals[k][mappings[k]];
      }
    }

    double scale = 1.0 / sum(m_array);
    for (Index index(m_array.sizes()); !index.end(); ++index)
    {
      m_array[index] *= scale;    
    }

    return m_array;
  }

  NDArray<double>& doIPF()
  {
    Index index_main(m_array.sizes());
    
    std::vector<MappedIndex> mappings;
    mappings.reserve(m_marginals.size());
    for (size_t k = 0; k < m_marginals.size(); ++k)
    {
      mappings.push_back(MappedIndex(index_main, m_indices[k]));
    }

    m_array.assign(1.0);

    marginal_list_t diffs(m_marginals.size());
    m_errors.resize(m_marginals.size());
    
    for (size_t k = 0; k < diffs.size(); ++k)
    {
      diffs[k].resize(m_marginals[k].sizes());
      m_errors[k].resize(m_marginals[k].sizes());
    }

    m_conv = false;
    for (m_iters = 0; !m_conv && m_iters < 3; ++m_iters)
    {
      rScale(/*m_array, m_marginals*/);
      rDiff(diffs, m_array, m_marginals);

      m_conv = computeErrors(diffs);
    }

    return m_array;
  }

private:

  size_t m_dim;
  size_t m_iters;
  bool m_conv;
  index_list_t m_indices;
  marginal_list_t& m_marginals;
  marginal_list_t m_errors;
  marginal_indices_list_t m_dim_lookup;
  NDArray<double> m_array;
  double m_maxError;
  const double m_tol = 1e-8;
};

void doMd()
{
  std::vector<NDArray<double>> m;
  std::vector<std::vector<int64_t>> i;
  i.push_back(std::vector<int64_t>{0,1});
  i.push_back(std::vector<int64_t>{2,1});
  //i.push_back(std::vector<int64_t>{0});
  //i.push_back(std::vector<int64_t>{1});
  //i.push_back(std::vector<int64_t>{2,0});
  NDArray<double> m0(std::vector<int64_t>{2, 3});
  m0.assign(5.0);
  NDArray<double> m1(std::vector<int64_t>{5, 3});
  m1.assign(2.0);
  NDArray<double> m2(std::vector<int64_t>{5, 2});
  m2.assign(9.0);
  // induce partial sum mismatch
  // Index idx(m1.sizes());
  // m1[idx] += 0.1;
  // m1[++idx] -= 0.1;

  m.push_back(std::move(m0));
  m.push_back(std::move(m1));
  //m.push_back(std::move(m2));
  MIPF<double> mipf(i, m);
  // {
  //   const auto& a = mipf.doP();
  //   print(a.rawData(), a.storageSize());
  //   std::cout << sum(a) << std::endl;
  // }
  {
    const auto& a = mipf.doIPF();
    print(a.rawData(), a.storageSize());
    std::cout << sum(a) << std::endl;
  }
}

int main()
{
  try
  {
    do2d();
    do3d();
    do4d();

    std::vector<int64_t> s{3,2,5};
    NDArray<double> a(s);
    a.assign(1.0);
    for (Index index(a.sizes(), {0,1}); !index.end(); ++index)
    {
      ++a[index];
    }
    for (Index index(a.sizes(), {1,0}); !index.end(); ++index)
    {
      ++a[index];
    }
    for (Index index(a.sizes(), {2,2}); !index.end(); ++index)
    {
      ++a[index];
    }
    print(a.rawData(), a.storageSize(), s[2]);

    print(reduce(a, 0));
    print(reduce(a, 1));
    print(reduce(a, 2));

    for (size_t d = 0; d < a.dim(); ++d)
    {
      for (int64_t i = 0; i < a.sizes()[d]; ++i)
      {
        NDArray<double> a00 = slice(a, {d,i});
        print(a00.rawData(), a00.storageSize());//, a00.sizes()[1]);
      }
    }

    do2dIPF();
    do3dIPF();

    {
      NDArray<double> r = reduce(a, std::vector<int64_t>{0,1});

      std::cout << r.dim() << std::endl;
      print(r.sizes());
      print(r.rawData(), r.storageSize(), r.sizes()[1]);
    }
    {
      NDArray<double> r = reduce(a, std::vector<int64_t>{1,2});

      std::cout << r.dim() << std::endl;
      print(r.sizes());
      print(r.rawData(), r.storageSize(), r.sizes()[1]);
    }
    {
      NDArray<double> r = reduce(a, std::vector<int64_t>{2, 0});

      std::cout << r.dim() << std::endl;
      print(r.sizes());
      print(r.rawData(), r.storageSize(), r.sizes()[1]);
    }

    doMd();
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "unknown exception" << std::endl;
  }  
}