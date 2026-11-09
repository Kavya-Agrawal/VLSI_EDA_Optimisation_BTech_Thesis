// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79982110;
  double density_weight = 0.00922328;
  double prefix_weight = 0.32231115;
  double neighborhood_weight = 0.07621959;
  double late_weight = 0.29539777;
  double critical_weight = 0.42080987;
  unsigned budget = 16;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
