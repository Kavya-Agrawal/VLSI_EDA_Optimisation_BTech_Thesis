// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99105774;
  double density_weight = 0.26416590;
  double prefix_weight = 0.09736256;
  double neighborhood_weight = 0.10244785;
  double late_weight = 0.17862091;
  double critical_weight = 0.28159062;
  unsigned budget = 12;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
